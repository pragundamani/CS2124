#include <iostream>

using namespace std;

class length{
    int meter;
public:
    length(int meter): meter(meter){ }
//by using explicit we prevent unintended conversions
//explicit length(int meter) :meter(meter){ }
};


int main(){
    double d = 5; // a double is created with the value of 5.0 implicitly
    length(b) = 5; // a length object with the value of 5 implicitly
    
    //length(b) = 5 would fail
    length(c) = length(5); // a length object with the value of 5 explicitly
}

//ask for questions to practice over the week

/*
* begin() points to item 1 of the vector
* end() points to the position after the last item of the vector
*/

