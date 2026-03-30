#include <iostream>

using namespace std;

class Base {
public:
    void foo(int n) const { cout << "Base::foo(n)\n"; }
};

class Derived : public Base {
public:
    //we can have a wrapper for every function but its easier to do a using
    using Base::foo;
    void foo() const { cout << "Derived::foo()"; }
};

int main(){
    Derived der;
    //der.foo(17);
    der.Base::foo(17);
}
