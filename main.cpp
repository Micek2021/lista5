#include <iostream>
#include <string>
#include "expressiontree.h"
#include "processor.h"

int main() {
    ExpressionTree tree;
    InputProcessor processor;

    std::cout << "enter\n";
    std::cout << "vars\n";
    std::cout << "print\n";
    std::cout << "comp\n";
    std::cout << "join\n";
    std::cout << "exit\n";

    std::string input;
    while (std::getline(std::cin, input)) {
        processor.processInput(input)->evaluate(tree);
    }

    return 0;
}