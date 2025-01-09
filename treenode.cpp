#include "treenode.h"

#include <cmath>
#include <cstdlib>


TreeNode::TreeNode(const std::string &val, const int expectedChildNum): value(val), expectedChildNumber(expectedChildNum) {}

TreeNode::~TreeNode() {
    for (std::vector<TreeNode*>::iterator ii = children.begin(); ii != children.end(); ii++) {
        delete *ii;
    }
}

TreeNode *TreeNode::clone() const {
    TreeNode *cloned = createClone();
    for (std::vector<TreeNode*>::const_iterator ii = children.begin(); ii != children.end(); ii++) {
        cloned->children.push_back((*ii)->clone());
    }
    return cloned;
}


Add::Add(const std::string &val): TreeNode(val, 2) {}

ResultHolder<double, ErrorInfo> Add::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    if(!children[1]->makeValue().isSuccess()) {
        return children[1]->makeValue();
    }
    //modyfikacja
    if(!(children[0]->expectedChildNumber != 0 || children[1]->expectedChildNumber != 0)) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(NOOPERATORINSUM));
    }
    return ResultHolder<double, ErrorInfo>::success(children[0]->makeValue().getValue()+children[1]->makeValue().getValue());
}

TreeNode *Add::createClone() const {
    return new Add(this->value);
}


Sub::Sub(const std::string &val): TreeNode(val, 2) {}

ResultHolder<double, ErrorInfo> Sub::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    if(!children[1]->makeValue().isSuccess()) {
        return children[1]->makeValue();
    }
    return ResultHolder<double, ErrorInfo>::success(children[0]->makeValue().getValue() - children[1]->makeValue().getValue());
}

TreeNode* Sub::createClone() const {
    return new Sub(this->value);
}


Mul::Mul(const std::string &val): TreeNode(val, 2) {}

ResultHolder<double, ErrorInfo> Mul::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    if(!children[1]->makeValue().isSuccess()) {
        return children[1]->makeValue();
    }
    return ResultHolder<double, ErrorInfo>::success(children[0]->makeValue().getValue() * children[1]->makeValue().getValue());
}

TreeNode *Mul::createClone() const {
    return new Mul(this->value);
}


Div::Div(const std::string &val): TreeNode(val, 2) {}

ResultHolder<double, ErrorInfo> Div::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    if(!children[1]->makeValue().isSuccess()) {
        return children[1]->makeValue();
    }
    if(children[1]->makeValue().getValue() == 0) {
       return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(DIVISIONBYZEROERRORINFO));
    }
    return ResultHolder<double, ErrorInfo>::success(children[0]->makeValue().getValue() / children[1]->makeValue().getValue());
}

TreeNode *Div::createClone() const {
    return new Div(this->value);
}


Pow::Pow(const std::string &val): TreeNode(val, 2) {}

ResultHolder<double, ErrorInfo> Pow::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    if(!children[1]->makeValue().isSuccess()) {
        return children[1]->makeValue();
    }
    return ResultHolder<double, ErrorInfo>::success(pow(children[0]->makeValue().getValue(), children[1]->makeValue().getValue()));
}

TreeNode *Pow::createClone() const {
    return new Pow(this->value);
}


Sin::Sin(const std::string &val): TreeNode(val, 1) {}

ResultHolder<double, ErrorInfo> Sin::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    return ResultHolder<double, ErrorInfo>::success(sin(children[0]->makeValue().getValue()));
}

TreeNode *Sin::createClone() const {
    return new Sin(this->value);
}


Cos::Cos(const std::string &val): TreeNode(val, 1) {}

ResultHolder<double, ErrorInfo> Cos::makeValue() const {
    if (expectedChildNumber > children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOFEWCHILDRENERRORINFO));
    }
    if (expectedChildNumber < children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    if(!children[0]->makeValue().isSuccess()) {
        return children[0]->makeValue();
    }
    return ResultHolder<double, ErrorInfo>::success(cos(children[0]->makeValue().getValue()));
}

TreeNode *Cos::createClone() const {
    return new Cos(this->value);
}


Value::Value(const std::string &val): TreeNode(val, 0) {}


ResultHolder<double, ErrorInfo> Value::makeValue() const {
    if (expectedChildNumber != children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    } else{
        char *endPtr;
        return ResultHolder<double, ErrorInfo>::success(std::strtod(value.c_str(), &endPtr));
    }
}

TreeNode *Value::createClone() const {
    return new Value(this->value);
}


Variable::Variable(const std::string &val): TreeNode(val, 0) {}

ResultHolder<double, ErrorInfo> Variable::makeValue() const {
    if (expectedChildNumber != children.size()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo(TOOMANYCHILDRENERRORINFO));
    }
    std::map<std::string, std::pair<double, int> >::const_iterator it = variables->find(value);
    if (it == variables->end()) {
        return ResultHolder<double, ErrorInfo>::failure(new ErrorInfo("Variable not found: " + value));
    }
    return ResultHolder<double, ErrorInfo>::success(variables->at(value).first);
}

TreeNode *Variable::createClone() const {
    return new Variable(this->value);
}