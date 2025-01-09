#include "errorinfo.h"

ErrorInfo::ErrorInfo(): errorMessage("") {}

ErrorInfo::ErrorInfo(std::string errorDescription): errorMessage(errorDescription) {}

ErrorInfo::~ErrorInfo() {}

std::string ErrorInfo::getErrorMessage() {
    return errorMessage;
}

void ErrorInfo::setErrorMessage(std::string newErrorDescription) {
    errorMessage = newErrorDescription;
}