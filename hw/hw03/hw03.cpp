/*
Pragun Damani
hw03.cpp
Spring 2026
*/

#include <cstddef>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <type_traits>
#include <vector>
#include <string>

using namespace std;

class Warrior{
    string name;
    string weapon;
    int strength;
};

int main(){
  vector<Warrior> warriors; //stores all of our warriors
  ifstream warriorStream("warriors.txt");
  if (!warriorStream){
      cerr << "Error: could not open warrior.txt";
      exit(1);
  }
  
  //read and exec commands in order of text
    
  return 0;  
};
