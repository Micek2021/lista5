#include <sstream>
#include "processor.h"
#include "evaluator.h"


InputProcessor::~InputProcessor() {
    delete evaluator;
}


Evaluator *InputProcessor::processInput(const std::string &input) {
    std::istringstream iss(input);
    std::string expression;
    std::string remainingWords;

    iss >> expression;


    size_t pos = input.find(expression) + expression.length();
    if (pos < input.length()) {
        remainingWords = input.substr(pos + 1);
    }

    delete evaluator;


    if (expression == ENTER_COMMAND) {
        evaluator = new EnterEvaluator(remainingWords);
    } else if (expression == VARS_COMMAND) {
        evaluator = new VarsEvaluator;
    } else if (expression == PRINT_COMMAND) {
        evaluator = new PrintEvaluator;
    } else if (expression == COMP_COMMAND) {
        evaluator = new CompEvaluator(remainingWords);
    } else if (expression == JOIN_COMMAND) {
        evaluator = new JoinEvaluator(remainingWords);
    } else if (expression == EXIT_COMMAND) {
        evaluator = new ExitEvaluator;
    } else {
        evaluator = new InvalidEvaluator;
    }


    return evaluator;
}
