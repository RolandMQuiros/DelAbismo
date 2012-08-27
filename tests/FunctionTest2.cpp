#include <functional>
#include <iostream>

int num = 0;

void func() {
    std::cout << num << std::endl;
}

int main() {
    num = 10;
    std::function<void()> func1(std::bind(func));
    
    num = 20;
    std::function<void()> func2(std::bind(func));
    
    func1();
    func2();
    
    return 0;
}