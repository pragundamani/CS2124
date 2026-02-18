/*
PD
lec9.cpp
Spring 2026
*/

#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

class Vector{
public:
    Vector(){
        theSize = 0;
        theCapacity = 0;
    }
private:
    //we need:
    //size - size_t
    size_t theSize;
    //capacity - size_t
    size_t theCapacity;
    //data - pointer
    int* data; //does data point to the start of the array as in the first int?
};

int main(){
    Vector<int> v; //
}
