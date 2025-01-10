#pragma once

#include <list>
#include <sstream>

#include "treenode.h"

class ExpressionTree {
public:
    ExpressionTree();

    ExpressionTree(const ExpressionTree& other);

    ExpressionTree(ExpressionTree &&other) noexcept;

    ~ExpressionTree();

    ResultHolder<ExpressionTree*, ErrorInfo> loadExpression(const std::string &expression);

    ResultHolder<void, ErrorInfo> fillVars(const std::vector<double> &values);

    ResultHolder<double, ErrorInfo> calculate() const;

    ExpressionTree operator=(ExpressionTree &expressionTree);

    ExpressionTree operator=(ExpressionTree&& other) noexcept;

    ExpressionTree operator+(const ExpressionTree &other) const;

    ExpressionTree operator+(ExpressionTree&& other) noexcept;

    std::string getVariables() const;

    friend std::ostream & operator<<(std::ostream &os, const ExpressionTree &expressionTree);

    void clearArgumentMap();

private:
    void dfs(TreeNode *node);

    TreeNode *buildTree(std::list<std::string> &tokens);

    std::string toString(TreeNode *node) const;

    void join(const ExpressionTree& tree);

    TreeNode* defineTree(const std::string &s);

    bool isTreeComplete(TreeNode *node) const;

    TreeNode *root;
    std::map<std::string, std::pair<double, int>> variables;
};

std::ostream& operator<<(std::ostream &os, const ExpressionTree &obj);