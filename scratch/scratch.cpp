#include <iostream>
using namespace std;

void foo(int& x) {
    int* const p = &x;   // line A
    x = 6;               // line B
    cout << *p << ' ';   // line C
    *p = 28;             // line D
}

int main() {
    int y = 42;
    foo(y);
    cout << y << endl;
}
