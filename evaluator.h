#pragma once

#include <string>
#include <vector>
#include "expressiontree.h"



class Evaluator {
protected:
    std::string arguments;
public:
    explicit Evaluator(const std::string &args) : arguments(args) {}

    Evaluator() : arguments("") {}

    virtual ~Evaluator() {}

    virtual void evaluate(ExpressionTree &tree) const = 0;
};

class EnterEvaluator : public Evaluator {
public:
    EnterEvaluator() : Evaluator("") {} // Konstruktor domyślny
    EnterEvaluator(const std::string &args) : Evaluator(args) {}

    void evaluate(ExpressionTree &tree) const;
};

class VarsEvaluator : public Evaluator {
public:
    VarsEvaluator() : Evaluator("") {}
    VarsEvaluator(const std::string &args) : Evaluator(args) {}

    void evaluate(ExpressionTree &tree) const;
};

class PrintEvaluator : public Evaluator {
public:
    PrintEvaluator() : Evaluator("") {}
    PrintEvaluator(const std::string &args) : Evaluator(args) {}

    void evaluate(ExpressionTree &tree) const;
};

class CompEvaluator : public Evaluator {
public:
    CompEvaluator() : Evaluator("") {}
    CompEvaluator(const std::string &args) : Evaluator(args) {}

    void evaluate(ExpressionTree &tree) const;
};

class JoinEvaluator : public Evaluator {
public:
    JoinEvaluator() : Evaluator("") {}
    JoinEvaluator(const std::string &args) : Evaluator(args) {}

    void evaluate(ExpressionTree &tree) const;
};

class InvalidEvaluator : public Evaluator {
public:
    InvalidEvaluator() : Evaluator("") {}
    InvalidEvaluator(const std::string &args) : Evaluator(args) {}

    ~InvalidEvaluator() {}

    void evaluate(ExpressionTree &tree) const;
};

class ExitEvaluator : public Evaluator {
public:
    ExitEvaluator() : Evaluator("") {}
    ExitEvaluator(const std::string &args) : Evaluator(args) {}

    void evaluate(ExpressionTree &tree) const;
};
