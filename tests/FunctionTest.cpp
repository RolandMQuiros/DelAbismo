#include <functional>
#include <iostream>
#include <limits.h>

class IFoo {
public:
    virtual void func()=0;

};

class Foo : public IFoo {
public:
    void func() {
        unsigned int i, j, k;
        unsigned int l = i * j * k;
    }
};

void func() {
    unsigned int i, j, k;
    unsigned int l = i * j * k;
}

int main() {
    // Virtual method vs. std::function
    
    // Virtual method
    IFoo *fuu = new Foo();
    for (unsigned int i = 0; i < 1E6; i++) {
        fuu->func();
    }
    
    /*
    // std::function
    std::function<void()> fun(func);
    for (unsigned int i = 0; i < 1E6; i++) {
        fun();
    }*/
    
    return 0;
}
