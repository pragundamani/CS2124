/*
PD
lec9.cpp
Spring 2026
*/

#include <iostream>
using namespace std;

int main() {
    int x =17, y =42;
    //to define a pointer that cannot be changed
    const int* p = &x; //stops it from modifying
    // *p = 28;
    int* const q = &x; //stops it from reassignment
    // q = &y;

    const int z = 100;
    const int* r = &z;
    //*r = 101; stops it from exisitng

    cout << p;
    return 0;
    //dont pass pointers by constant reference

    //use new keyword to initialize a new object when adding references to a vector
    //if you use new use delete to free it up new has to go with delete
    //delete frees up pointers contents,
}
