    #include <functional>
    #include <iostream>

    struct Foo {
        int num;
        
        void bar() const {
            std::cout << num << std::endl;
        }
    };

    int main() {
        Foo *foo = new Foo();
        foo->num = 1896;
        std::function<void()> func1(std::bind(&Foo::bar, *foo));
        delete foo;
        
        func1(); // THIS STILL WORKS.  THIS SHOULD SEGFAULT.  WHAT IS THIS SORCERY.
        
        return 0;
    }
