#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "resultholder.h"
#include "errorinfo.h"
#include "expressiontree.h"

template <typename T>
class ResultSaver {
public:
    static void saveToFile(const ResultHolder<T, ErrorInfo>& result, const std::string& filename) {
        std::ofstream outFile(filename.c_str(), std::ios::app);
        if (!outFile.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        if (result.isSuccess()) {
            outFile << "Operation successful." << std::endl;
        } else {
            const std::vector<ErrorInfo*>& errors = result.getErrorList();
            for (typename std::vector<ErrorInfo*>::const_iterator it = errors.begin(); it != errors.end(); ++it) {
                outFile << "Error: " << (*it)->getErrorMessage() << std::endl;
            }
        }

        outFile.close();
    }
};

template <>
class ResultSaver<ExpressionTree*> {
public:
    static void saveToFile(const ResultHolder<ExpressionTree*, ErrorInfo>& result, const std::string& filename) {
        std::ofstream outFile(filename.c_str(), std::ios::app);
        if (!outFile.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        if (result.isSuccess()) {
            ExpressionTree* tree = result.getValue();
            if (tree) {
                outFile << "Tree (prefix form): " << *tree << std::endl;
            } else {
                outFile << "No tree to save." << std::endl;
            }
        } else {
            const std::vector<ErrorInfo*>& errors = result.getErrorList();
            for (typename std::vector<ErrorInfo*>::const_iterator it = errors.begin(); it != errors.end(); ++it) {
                outFile << "Error: " << (*it)->getErrorMessage() << std::endl;
            }
        }

        outFile.close();
    }
};
