cmake_minimum_required(VERSION 3.29)
project(lista5)

set(CMAKE_CXX_STANDARD 11)

add_executable(lista5 main.cpp
        treenode.cpp
        treenode.h
        resultholder.h
        errorinfo.cpp
        errorinfo.h
        constants.h
        expressiontree.cpp
        expressiontree.h
        resultsaver.h
        evaluator.cpp
        evaluator.h
        processor.cpp
        processor.h
        smartpointer.h
        RefCounter.cpp
        RefCounter.h)
