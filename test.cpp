#include <iostream>
#include <unordered_set>
#include "safe_pointer.h"
using namespace glaiel;



class Foo {
    public:
    int bar = 10;
    
    SAFE_POINTABLE;
};



int main() {
    Foo* foo = new Foo();
    Foo* foo2 = new Foo();
    

    safe_pointer<Foo> pfoo = foo;
    
    safe_pointer<Foo> pfoo2;
    pfoo2 = foo;
    
    *foo = *foo2;
    
    std::cout << (Foo*)pfoo << std::endl;
    std::cout << (Foo*)pfoo2 << std::endl;
    delete foo;
    std::cout << (Foo*)pfoo << std::endl;
    std::cout << (Foo*)pfoo2 << std::endl;
    
    delete foo2;
    
    return 0;
}
