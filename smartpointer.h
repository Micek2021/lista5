#pragma once

#include "refcounter.h"

template<typename T>

class SmartPointer {
private:
T *rawPointer;
RefCounter *referenceCounter;

public:
    SmartPointer(T *inputPointer) {
        if (inputPointer == nullptr) {
            rawPointer = nullptr;
            referenceCounter = nullptr;
        }else {
            rawPointer = inputPointer;
            referenceCounter = new RefCounter;
            referenceCounter->increment();
        }
    }

    SmartPointer(const SmartPointer &other) {
        rawPointer = other.rawPointer;
        referenceCounter = other.referenceCounter;
        referenceCounter->increment();
    }

    ~SmartPointer() {
        if(referenceCounter->decrement()==0) {
            delete rawPointer;
            delete referenceCounter;
        }
    }

    SmartPointer& operator=(const SmartPointer &other) {
        if (this != &other) {
            if(referenceCounter && referenceCounter->decrement() ==0) {
                delete rawPointer;
                delete referenceCounter;
            }

            rawPointer = other.rawPointer;
            referenceCounter = other.referenceCounter;
            referenceCounter->increment();
        }
        return *this;
    }

    T& operator*() { return(*rawPointer); }
    T* operator->(){return(rawPointer);}

    T* getValue() const { return rawPointer; }
};