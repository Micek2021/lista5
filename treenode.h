#pragma once

#include "resultholder.h"
#include "errorinfo.h"
#include "constants.h"

#include <map>

class TreeNode {
public:
    std::string value;
    std::vector<TreeNode*> children;
    int expectedChildNumber;

    TreeNode(const std::string &val, const int expectedChildNum);

    virtual ~TreeNode();

    virtual ResultHolder<double, ErrorInfo> makeValue() const = 0;

    virtual TreeNode *clone() const;

protected:
    virtual TreeNode *createClone() const = 0;
};


class Add : public TreeNode {
public:
    explicit Add(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Sub : public TreeNode {
public:
    explicit Sub(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Mul : public TreeNode {
public:
    explicit Mul(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Div : public TreeNode {
public:
    explicit Div(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Pow : public TreeNode {
public:
    explicit Pow(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Sin : public TreeNode {
public:
    explicit Sin(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Cos : public TreeNode {
public:
    explicit Cos(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Value : public TreeNode {
public:
    explicit Value(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

protected:
    TreeNode *createClone() const;
};


class Variable : public TreeNode {
public:
    explicit Variable(const std::string &val);

    ResultHolder<double, ErrorInfo> makeValue() const;

    std::map<std::string, std::pair<double, int> > *variables;

protected:
    TreeNode *createClone() const;
};