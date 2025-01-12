#include <iostream>
#include <string>
#include "expressiontree.h"
#include "processor.h"
#include "smartpointer.h"

void useSmartPointer() {
    SmartPointer<int> ptr1(new int(10));
    SmartPointer<int> ptr2 = ptr1;

    std::cout << "Value: " << *ptr1 << std::endl;
    std::cout << "Value: " << *ptr2 << "\n\n\n\n\n";
}

int main() {
    //testy = i +
    ExpressionTree tree;
    InputProcessor processor;

    ExpressionTree tree1;
    ExpressionTree tree2;

    std::cout << "Test konstruktorow i przypisania:" << std::endl;

    ExpressionTree tree3 = tree1;
    std::cout << "tree3 - " <<tree3.toStringCopyMoveCount();

    tree3 = tree2;
    std::cout << "tree3 after assignment - " << tree3.toStringCopyMoveCount();

    ExpressionTree tree4 = std::move(tree1);
    std::cout << "tree4 - " << tree4.toStringCopyMoveCount();

    tree4 = std::move(tree2);
    std::cout << "tree4 after move assignment - " << tree4.toStringCopyMoveCount();

    std::cout << "\nTest operatora dodawania:" << std::endl;

    ExpressionTree tree5 = tree3 + tree4;
    std::cout << "tree5 - " << tree5.toStringCopyMoveCount();

    ExpressionTree tree6 = std::move(tree3) + std::move(tree4);
    std::cout << "tree6 - " << tree6.toStringCopyMoveCount() << "\n\n\n\n\n";

    //Test smartpointera
    useSmartPointer();

    //menu
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