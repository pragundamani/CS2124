/*
PD
lec16.cpp
Spring 2026
*/

#include <iostream>

using namespace std;

class Pet {
public:
    Pet (const string& name) : name(name) { }

    //void eat() { cout << "Eating \n"; } 
    virtual void eat() { cout << "Eating \n"; }
private:
    string name;
};

class Cat : public Pet {
public:
    //Cat (const string& name) : name(name) { } //cannot innitialize because name is a pet fild not cat field
    Cat (const string& name) : Pet(name) /* call the Pet cosntructor */ { }
    //cat cannot access private items in base class so we need to use setters and getters later

    //void eat() { cout << "Cat eating \n"; }
	void eat() {
		cout << "Cat ";
        //eat() //infinite recursionc alling cat::eat
        Pet::eat();
    }
    void purr() { cout << "cat purr \n"; }


};

class Slug : public Pet { };
class Roach : public Pet { };


//void someFunc(Pet aPet) { //slicing problem: when you copy a chid class in a func, only the parent gets copied over
void someFunc(Pet& aPet) { //polymorphism: if a method is present for a child class use that
	cout << "someFunc: ";
	aPet.eat();
    //aPet.purr(); //compile time error    
}

int main(){
	//Pet peeve;
    //Pet peeve(); looks like it will make an empty name, but actually its a prototype
	Pet peeve("peeve");
    peeve.eat();
	someFunc(peeve);

	//Cat felix;
	Cat felix("Felix"); //chidlren do not inherit constructors
	
    felix.eat(); //code reuse
	someFunc(felix); //Principle of Substitutability (Barbara Liskov, turing award winner)
}
