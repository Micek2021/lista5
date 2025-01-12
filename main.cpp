#include <iostream>
#include <string>
#include "expressiontree.h"
#include "processor.h"

int main() {
    ExpressionTree tree;
    InputProcessor processor;

    ExpressionTree tree1;
    ExpressionTree tree2;

    std::cout << "Test konstruktorow i przypisania:" << std::endl;

    ExpressionTree tree3 = tree1;
    std::cout << "tree3 - Copies: " << tree3.getCopyCount()
              << ", Moves: " << tree3.getMoveCount() << std::endl;

    tree3 = tree2;
    std::cout << "tree3 after assignment - Copies: " << tree3.getCopyCount()
              << ", Moves: " << tree3.getMoveCount() << std::endl;

    ExpressionTree tree4 = std::move(tree1);
    std::cout << "tree4 - Copies: " << tree4.getCopyCount()
              << ", Moves: " << tree4.getMoveCount() << std::endl;

    tree4 = std::move(tree2);
    std::cout << "tree4 after move assignment - Copies: " << tree4.getCopyCount()
              << ", Moves: " << tree4.getMoveCount() << std::endl;

    std::cout << "\nTest operatora dodawania:" << std::endl;

    ExpressionTree tree5 = tree3 + tree4;
    std::cout << "tree5 - Copies: " << tree5.getCopyCount()
              << ", Moves: " << tree5.getMoveCount() << std::endl;

    ExpressionTree tree6 = std::move(tree3) + std::move(tree4);
    std::cout << "tree6 - Copies: " << tree6.getCopyCount()
              << ", Moves: " << tree6.getMoveCount() << std::endl << std::endl << std::endl << std::endl << std::endl;

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