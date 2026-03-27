#include <iostream>

class Base {
public:
private:
};

class Derived : public Base {
public:
private:
};

int main(){
    Base based;
    Derived deriver;

    Base* basePtr = nullptr;
    Derived* derPtr = nullptr;
    
    based = deriver;
    //deriver = based; Guessing it has more than just base data 

    basePtr = &deriver;
    //derPtr = &based; //has more than just base
   
    basePtr = &based;
    derPtr = &deriver;

    basePtr = nullptr;
    derPtr = nullptr;



    return 0;
}
