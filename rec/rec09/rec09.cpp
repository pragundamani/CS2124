#include <iostream>
using namespace std;

class A {
public:
    void x() {
        this->y();
        this->z();
    }
    void y() {
        cout << "A::y()" << endl;
    }
    virtual void z() {
        cout << "A::z()" << endl;
    }
};

class B: public A {
public:
    void y() {
        cout << "B::y()" << endl;
    }
    void z() {
        cout << "B::z()" << endl;
    }
};

class C: public B {
public:
    void z() {
        cout << "C::z()" << endl;
    }
};

int main() {
    cout << "Using A*\n";
    A* aPtr = new B();
    aPtr->y(); // What does this print?
    aPtr->z(); // What does this print?

    cout << "Using B*\n";
    B* bPtr = new B();
    bPtr->x(); // What does this print?
    bPtr->y(); // What does this print?
    bPtr->z(); // What does this print?

    cout << "bPtr pointint to C\n";
    bPtr = new C();
    bPtr->z(); // What does this print?
}
