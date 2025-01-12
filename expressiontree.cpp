#include "ExpressionTree.h"

#include <algorithm>
#include <list>
#include <cctype>
#include <numeric>
#include <string>
#include <iostream>

namespace {
    struct IsNotAlNum {
        bool operator()(char c) const {
            return !std::isalnum(static_cast<unsigned char>(c));
        }
    };

    std::string createWithAlNum(const std::string &input) {
        std::string output = input;
        output.erase(
            std::remove_if(output.begin(), output.end(), IsNotAlNum()),
            output.end()
        );
        return output;
    }
}

TreeNode *ExpressionTree::defineTree(const std::string &s) {
    if (!s.empty() && s.find_first_not_of(ALL_DIGITS) == std::string::npos) {
        return new Value(s);
    }
    if (s == SIN_FUNC) {
        return new Sin(s);
    }
    if (s == COS_FUNC) {
        return new Cos(s);
    }
    if (s == PLUS_SIGN) {
        return new Add(s);
    }
    if (s == MINUS_SIGN) {
        return new Sub(s);
    }
    if (s == MUL_SIGN) {
        return new Mul(s);
    }
    if (s == DIV_SIGN) {
        return new Div(s);
    }

    std::string input = createWithAlNum(s);
    if (!input.empty()) {
        Variable *node = new Variable(input);
        node->variables = &variables;

        if (variables.find(node->value) != variables.end()) {
            variables[node->value].second++;
        } else {
            variables.insert(std::make_pair(node->value, std::make_pair(-1, 1)));
        }

        return node;
    }

    return NULL;
}

ExpressionTree::ExpressionTree() : root(NULL), moveCount(0), copyCount(0) {}

ExpressionTree::~ExpressionTree() {
    delete root;
}

ExpressionTree::ExpressionTree(const ExpressionTree &other)
    : root(other.root != NULL ? other.root->clone() : NULL),
      variables(other.variables),
      copyCount(other.copyCount +1),
      moveCount(other.getMoveCount())
    {
    if (root != NULL) {
        dfs(root);
    }
}

ExpressionTree::ExpressionTree(ExpressionTree &&other) noexcept{
    root = other.root;
    other.root = nullptr;
    variables = std::move(other.variables);
    copyCount = other.copyCount;
    moveCount = other.moveCount + 1;
    if(root) {
        dfs(root);
    }
}

ExpressionTree ExpressionTree::operator=(ExpressionTree &&other) noexcept {
    if (this != &other) {
        delete root;
        root = other.root;
        other.root = nullptr;
        variables = std::move(other.variables);
        moveCount = this->moveCount + other.moveCount + 1;
        copyCount = this->copyCount +  other.copyCount;
        if (root != nullptr) {
            dfs(root);
        }
    }
    return *this;
}

ExpressionTree ExpressionTree::operator=(ExpressionTree &other) {
    variables = other.variables;
    std::swap(root, other.root);
    if (root != NULL) {
        dfs(root);
    }

    moveCount = this->moveCount + other.moveCount;
    copyCount = this->copyCount +  other.copyCount + 1;

    return *this;
}

TreeNode *ExpressionTree::buildTree(std::list<std::string> &tokens) {
    if (tokens.empty()) {
        return NULL;
    }

    std::string front = tokens.front();
    tokens.pop_front();

    TreeNode *treeNode = defineTree(front);
    if (treeNode == NULL) {
        return NULL;
    }

    for (int i = 0; i < treeNode->expectedChildNumber; i++) {
        if (!tokens.empty()) {
            TreeNode *child = buildTree(tokens);
            treeNode->children.push_back(child);
        } else {
            treeNode->children.push_back(NULL);
        }
    }

    return treeNode;
}

ResultHolder<ExpressionTree*, ErrorInfo> ExpressionTree::loadExpression(const std::string& expression) {
    std::istringstream iss(expression);
    std::list<std::string> tokens;
    std::string token;

    while (iss >> token) {
        tokens.push_back(token);
    }

    TreeNode* newRoot = buildTree(tokens);

    if (!tokens.empty()) {
        return ResultHolder<ExpressionTree*, ErrorInfo>::failure(new ErrorInfo(TOOBIGEXPRESSIONERRORINFO));
    }

    if (newRoot == NULL) {
        return ResultHolder<ExpressionTree*, ErrorInfo>::failure(new ErrorInfo(EMPTYROOTERRORINFO));
    }

    if (!isTreeComplete(newRoot)) {
        return ResultHolder<ExpressionTree*, ErrorInfo>::failure(new ErrorInfo(INCOMPLETETREELOADINGERRORINFO));
    }

    root = newRoot;
    moveCount = 0;
    copyCount = 0;
    return ResultHolder<ExpressionTree*, ErrorInfo>::success(this);
}


ResultHolder<void, ErrorInfo> ExpressionTree::fillVars(const std::vector<double> &values) {
    if (values.size() != variables.size()) {
        return ResultHolder<void, ErrorInfo>::failure(new ErrorInfo(DIFFERENT_ARGUMENT_MSG));
    }

    std::vector<double>::const_iterator vectorIterator = values.begin();
    for (std::map<std::string, std::pair<double, int> >::iterator mapElement = variables.begin();
         mapElement != variables.end();
         ++mapElement) {
        mapElement->second.first = *vectorIterator;
        ++vectorIterator;

    }
    return ResultHolder<void,ErrorInfo>::success();
}

std::string ExpressionTree::toString(TreeNode *node) const {
    if (node == NULL) {
        return "";
    }
    std::string result = node->value;
    for (std::vector<TreeNode *>::const_iterator child = node->children.begin();
         child != node->children.end(); ++child) {
        result += SPACE + toString(*child);
    }
    return result;
}

ExpressionTree ExpressionTree::operator+(const ExpressionTree &other) const {
    ExpressionTree result = *this;
    result.join(other);
    result.copyCount = this->copyCount + other.copyCount + 1;
    result.moveCount = this->moveCount + other.moveCount;
    return result;
}


ExpressionTree ExpressionTree::operator+(ExpressionTree &&other) noexcept {
    ExpressionTree result = std::move(*this);
    result.join(std::move(other));
    result.copyCount = this->copyCount + other.copyCount;
    result.moveCount = this->moveCount + other.moveCount + 1;
    return std::move(result);
}



void ExpressionTree::dfs(TreeNode *node) {
    if (node == NULL) return;

    Variable *var = dynamic_cast<Variable *>(node);
    if (var != NULL) {
        var->variables = &variables;
    }

    for (std::vector<TreeNode *>::iterator child = node->children.begin();
         child != node->children.end(); ++child) {
        dfs(*child);
    }
}

ResultHolder<double, ErrorInfo> ExpressionTree::calculate() const {
    return root->makeValue();
}

void ExpressionTree::join(const ExpressionTree &tree) {
    ExpressionTree other = tree;

    TreeNode *parent = root;
    while (parent != NULL && !parent->children.empty() && !parent->children[0]->children.empty()) {
        parent = parent->children[0];
    }

    TreeNode *child = (parent != NULL && !parent->children.empty()) ? parent->children[0] : parent;

    Variable *var = dynamic_cast<Variable *>(child);
    if (var != NULL) {
        std::map<std::string, std::pair<double, int> >::iterator it = variables.find(var->value);
        if (it != variables.end()) {
            if (it->second.second == 1) {
                variables.erase(it);
            } else {

                it->second.second--;
            }
        }
    }

    if (parent == root && (parent == NULL || parent->children.empty())) {
        root = other.root;
    } else if (parent != NULL) {
        parent->children[0] = other.root;
    }

    other.root = NULL;


    for (std::map<std::string, std::pair<double, int> >::iterator it = other.variables.begin();
         it != other.variables.end(); ++it) {
        std::map<std::string, std::pair<double, int> >::iterator existing = variables.find(it->first);
        if (existing != variables.end()) {
            existing->second.second += it->second.second;
        } else {
            variables.insert(*it);
        }
         }

    dfs(root);
}



std::string ExpressionTree::getVariables() const {
    std::string result;
    for (std::map<std::string, std::pair<double, int> >::const_iterator it = variables.begin();
         it != variables.end();
         ++it) {
        result += it->first + SPACE;
    }
    return result;
}

std::ostream &operator<<(std::ostream &os, const ExpressionTree &obj) {
    return os << obj.toString(obj.root);
}

void ExpressionTree::clearArgumentMap() {
    variables.clear();
}

bool ExpressionTree::isTreeComplete(TreeNode *node) const {
    if (node == NULL) {
        return false;
    }

    for (std::vector<TreeNode *>::const_iterator it = node->children.begin();
         it != node->children.end(); ++it) {
        if (!isTreeComplete(*it)) {
            return false;
        }
         }

    return true;
}

int ExpressionTree::getCopyCount() const {
    return copyCount;
}

int ExpressionTree::getMoveCount() const {
    return moveCount;
}

