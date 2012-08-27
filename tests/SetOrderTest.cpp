#include <set>
#include <iostream>

struct A {
    int num;
};

struct ALess {
    bool operator()(const A &a, const A &b) const {
        return a.num < b.num;
    }
};

int main() {
    std::set<A, ALess> testSet;
    
    A tmp;
    
    for (int i = 0; i < 10; i++) {
        tmp.num = i;
        testSet.insert(tmp);
    }
    
    for (std::set<A, ALess>::iterator iter = testSet.begin();
         iter != testSet.end(); iter++) {
        std::cout << iter->num << ", ";
    }
    std::cout << std::endl;
    
    return 0;
}
