#pragma once

#include <string>
#include "evaluator.h"

class InputProcessor {
private:
    Evaluator *evaluator;

public:
    InputProcessor() : evaluator(NULL) {}

    ~InputProcessor();

    Evaluator *processInput(const std::string &input);

};
