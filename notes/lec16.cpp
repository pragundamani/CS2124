/*
PD
lec16.cpp
Spring 2026
*/

#include <vector>
#include <iostream>

using namespace std;

class Pet {
public:
    Pet (const string& name) : name(name) { }
    Pet (){}

    //void eat() { cout << "Eating \n"; } 
    virtual void eat() { cout << "Eating \n"; }

    const string& getName() const { return name; }
private:
    string name;
};

//class Cat final : public Pet { //mark final before adding other classes not after
class Cat : public Pet {
public:
    //Cat (const string& name) : name(name) { } //cannot innitialize because name is a pet fild not cat field
    Cat (const string& name) : Pet(name) /* call the Pet cosntructor */ { }
    //cat cannot access private items in base class so we need to use setters and getters later

    //void eat() { cout << "Cat eating \n"; }
	//void eat() override { //override is used for overwriting a method and helps catch errors
	void eat() {
		cout << "Cat ";
        //eat() //infinite recursionc alling cat::eat
        Pet::eat();
    }
    //void purr() { cout << name << " purr\n"; } name is a private field of pet
    //do not have fields in a class that are not private
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

    Slug sluggo;
    Roach archie;

    vector<Pet> menagerie;
    menagerie.push_back(peeve);
    menagerie.push_back(felix);
    menagerie.push_back(sluggo);
    menagerie.push_back(archie);

    for (size_t i =0; i<menagerie.size(); i++){
        menagerie[i].eat();
    }

    vector<Pet*> menagerie2;
        menagerie2.push_back(&peeve);
        menagerie2.push_back(&felix);
        menagerie2.push_back(&sluggo);
        menagerie2.push_back(&archie);

        for (size_t i =0; i<menagerie2.size(); i++){
            menagerie2[i]->eat();
        }
}
