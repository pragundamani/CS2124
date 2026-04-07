#include <iostream>
using namespace std;

class Base {
public: 
    Base() { this->foo(); }
    virtual void foo() const { cout << "Base \n"; }
    void display() {this->foo();}
};

class Derived : public Base {
public:
    Derived(int n) : Base(), x(n) { }
    void foo() const { cout << "Derived x: " << x << endl; }
private:
    int x;
};

int main(){
    Derived der(17);
    der.display();
}
