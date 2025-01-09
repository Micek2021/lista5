#pragma once

#include <string>

class ErrorInfo {
private:
    std::string errorMessage;
public:
    ErrorInfo();

    ErrorInfo(std::string errorDescription);

    ~ErrorInfo();

    std::string getErrorMessage();

    void setErrorMessage(std::string errorMessage);
};