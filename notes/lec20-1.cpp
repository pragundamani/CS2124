#include <iostream>
using namespace std;

class Flier{
public:
    virtual void fly() = 0; //not needed to be pure virtual in c++
};

class Animal {
public:
    virtual void display() { cout << "Animal \n"; } 
};

class Cat : public Animal {
public:
    void purr() { cout << "purr.. \n"; }
};

class Bat : public Animal {
public:
    void fly() { cout << "flap flap \n"; }
};

class Insect : public Animal {
public:
    void fly() { cout << "bzzz"; }
};

class Plane {
public:
    void fly() { cout << "vrooom"; }
};

//in inheritance left comes first

