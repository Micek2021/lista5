#pragma once

#include <vector>

template <typename T, typename E>
class ResultHolder {

private:
    T* valuePtr;
    std::vector<E*> errorList;

public:
    ResultHolder(const T& value): valuePtr(new T(value)), errorList() {}

    ResultHolder(E* error): valuePtr(nullptr), errorList() {errorList.push_back(error);}

    ResultHolder(std::vector<E*>& errorList): valuePtr(nullptr), errorList(errorList) {}

    ResultHolder(const ResultHolder<T, E>& other): valuePtr(other.valuePtr ? new T(*other.valuePtr) : nullptr), errorList(other.errorList) {}

    ~ResultHolder() {
        delete valuePtr;
        for (typename std::vector<E*>::iterator ii = errorList.begin(); ii != errorList.end(); ii++) {
            delete *ii;
        }
    }

    static ResultHolder<T, E> success(const T& value) {
        return ResultHolder<T, E>(value);
    }

    static ResultHolder<T, E> failure(E* error) {
        return ResultHolder<T, E>(error);
    }

    static ResultHolder<T, E> failure(std::vector<E*>& errors) {
        return ResultHolder<T, E>(errors);
    }

    ResultHolder<T, E>& operator=(const ResultHolder<T, E>& other) {
        if (this != &other) {
            delete valuePtr;
            for (typename std::vector<E*>::iterator ii = errorList.begin(); ii != errorList.end(); ii++) {
                delete *ii;
            }
            valuePtr = other.valuePtr ? new T(*other.valuePtr) : nullptr;
            errorList = other.errorList;
        }
    }

    bool isSuccess() const {
        return valuePtr != nullptr;
    }

    T getValue() const {
        return *valuePtr;
    }

    std::vector<E*>& getErrorList() {
        return errorList;
    }

    const std::vector<E*>& getErrorList() const {
        return errorList;
    }
};//ResultHolder<T, E>


template <typename E>
class ResultHolder<void, E> {
private:
    std::vector<E*> errorList;

public:
    ResultHolder(): errorList() {}

    ResultHolder(E* error): errorList() {errorList.push_back(error);}

    ResultHolder(std::vector<E*>& errorList): errorList(errorList) {}

    ~ResultHolder() {
        for (typename std::vector<E*>::iterator ii = errorList.begin(); ii != errorList.end(); ii++) {
            delete *ii;
        }
    }

    static ResultHolder<void, E> success() {
        return ResultHolder<void, E>();
    }

    static ResultHolder<void, E> failure(E* error) {
        return ResultHolder<void, E>(error);
    }

    static ResultHolder<void, E> failure(std::vector<E*>& errors) {
        return ResultHolder<void, E>(errors);
    }

    ResultHolder<void, E>& operator=(const ResultHolder<void, E>& other) {
        if (this != &other) {
            for (typename std::vector<E*>::iterator ii = errorList.begin(); ii != errorList.end(); ii++) {
                delete *ii;
            }
            errorList = other.errorList;
        }
        return *this;
    }

    bool isSuccess() const {
        return errorList.empty();
    }

    std::vector<E*>& getErrorList() {
        return errorList;
    }

    const std::vector<E*>& getErrorList() const {
        return errorList;
    }
};//Resultholder<void, E>