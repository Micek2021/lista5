#include "refcounter.h"

RefCounter::RefCounter():count(0){}

int RefCounter::increment() {return ++count;}

int RefCounter::decrement() {return --count;}

int RefCounter::getCount() {return count;}

RefCounter::~RefCounter() {}
