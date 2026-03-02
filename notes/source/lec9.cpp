/*
PD
lec9.cpp
Spring 2026
*/

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

class Vector {
public:
    Vector() : theSize(0), theCapacity(0), data(nullptr) {}

private:
    // we need:
    // size - size_t
    size_t theSize;
    // capacity - size_t
    size_t theCapacity;
    // data - pointer
    int* data; // points to the start of the array data on the heap
};

class Container {
public:
    Container(int value) : p(new int(value)) {}

    ~Container() {
        delete p;
    }

private:
    int* p;
};

int main() {
    int x = 3;
    int y = 42;
    int* p = &x;

    const int* readOnlyPtr = &x; // does not allow us to change x through the pointer
    int* const fixedPtr = &x;    // does not allow us to reassign the pointer

    // *readOnlyPtr = 28;
    // fixedPtr = &y;

    const int z = 100;
    const int* safePtr = &z;
    // *safePtr = 101;

    // memory leak is when program allocates memory on the heap
    int* q = new int(5); // have to delete after using
    delete q;

    int* a = new int[10]; // creates new array
    delete[] a;           // deletes an array

    // vector can store addresses, but the pointed-to objects still need a lifetime plan
    vector<int*> addresses;
    addresses.push_back(&x);
    addresses.push_back(&y);

    Vector v;
    Container c(17);
    (void)v;
    (void)c;

    cout << *p << ' ' << *readOnlyPtr << ' ' << *fixedPtr << ' ' << *safePtr << endl;
    cout << *addresses[0] << ' ' << *addresses[1] << endl;
}
