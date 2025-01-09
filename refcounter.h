#pragma once

class RefCounter {
private:
    int count;

public:
    RefCounter();

    int increment();
    int decrement();
    int getCount();

    ~RefCounter();
};
