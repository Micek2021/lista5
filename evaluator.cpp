#include "evaluator.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>

#include "resultsaver.h"


void EnterEvaluator::evaluate(ExpressionTree &tree) const {
    tree.clearArgumentMap();
    ResultHolder<ExpressionTree*, ErrorInfo> result = tree.loadExpression(arguments);
    ResultSaver<ExpressionTree*>::saveToFile(result, FILENAME);
    if (!result.isSuccess()) {
        std::cout << result.getErrorList().at(0)->getErrorMessage() << std::endl;
    }
}

void VarsEvaluator::evaluate(ExpressionTree &tree) const {
    std::string vars = tree.getVariables();
    if (vars.empty()) {
        std::cout << NO_ARG_MSG << std::endl;
    } else {
        std::cout << vars << std::endl;
    }
}

void PrintEvaluator::evaluate(ExpressionTree &tree) const {
    std::cout << tree << std::endl;
}

void CompEvaluator::evaluate(ExpressionTree &tree) const {
    std::vector<double> numbers;
    std::istringstream iss(arguments);
    std::string token;

    while (iss >> token) {
        char *endPtr = nullptr;
        double value = std::strtod(token.c_str(), &endPtr);

        if (endPtr != token.c_str() && *endPtr == '\0') {
            numbers.push_back(value);
        } else {
            std::cerr << INVALID_PARAM_MSG << std::endl;
            return;
        }
    }

    if (!tree.fillVars(numbers).isSuccess()) {
        return;
    }

    ResultHolder<double, ErrorInfo> result = tree.calculate();
    ResultSaver<double>::saveToFile(result, FILENAME);
    if (!result.isSuccess()) {
        std::cout << result.getErrorList().at(0)->getErrorMessage() << std::endl;
    } else {
        std::cout << result.getValue() << std::endl;
    }
}


void JoinEvaluator::evaluate(ExpressionTree &tree) const {
    ExpressionTree other;
    ResultHolder<ExpressionTree*, ErrorInfo> result = other.loadExpression(arguments);
    ResultSaver<ExpressionTree*>::saveToFile(result, FILENAME);
    if(!result.isSuccess()) {
        std::cout << result.getErrorList().at(0)->getErrorMessage() << std::endl;
    }else {
        tree = tree + other;
    }
}

void InvalidEvaluator::evaluate(ExpressionTree &tree) const {
    std::cerr << "Invalid command!" << std::endl;
}

void ExitEvaluator::evaluate(ExpressionTree &tree) const {
    std::cout << EXIT_MSG << std::endl;
    exit(0);
}

