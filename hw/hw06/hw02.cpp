/*
 Pragun Damani: pd2752
 hw02.cpp
 Spring 2026
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Warrior {
    string name;
    int strength; //using strength name 
};

// prototypes
void commands(ifstream& warriorStream, vector<Warrior>& warriors);
void warriorCommand(vector<Warrior>& warriors, const string& name,
                    int strength);
void battleCommand(vector<Warrior>& warriors, const string& firstName,
                   const string& secondName);
void statusCommand(const vector<Warrior>& warriors);
size_t findWarrior(const vector<Warrior>& warriors, const string& name);


int main() {
    vector<Warrior> warriors; //stores all warriors from file
    ifstream warriorStream("warriors.txt"); //input file
    if (!warriorStream) {
        cerr << "Error: could not open warriors.txt" << endl;
        exit(1);
    }

    //read and execute commands in order
    commands(warriorStream, warriors);

    return 0;
}

void commands(ifstream& warriorStream, vector<Warrior>& warriors) {
    string command; //temp var for each command
    while (warriorStream >> command) {
        //read fields that belong current command
        if (command == "Warrior") {
            string warriorName;
            int warriorStrength = 0;
            warriorStream >> warriorName >> warriorStrength;
            warriorCommand(warriors, warriorName, warriorStrength);
        }

        else if (command == "Battle") {
            string firstName;
            string secondName;
            warriorStream >> firstName >> secondName;
            battleCommand(warriors, firstName, secondName);
        }

        else if (command == "Status") {
            statusCommand(warriors);
        }
    }
}

void warriorCommand(vector<Warrior>& warriors,
    const string& name,int strength){
        // 
    //duplicate warrior names are not allowed
    if (findWarrior(warriors, name) != warriors.size()) {
        cerr << "Error: warrior " << name << " already exists" << endl;
        return;
    }

    //create new warrior and add to vector
    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;
    warriors.push_back(warrior);
}

void battleCommand(vector<Warrior>& warriors, const string& firstName,
                   const string& secondName) {
    //first output line for battle
    cout << firstName << " battles " << secondName << endl;

    //look up both warriors by name
    size_t firstIndex = findWarrior(warriors, firstName);
    size_t secondIndex = findWarrior(warriors, secondName);
    if (firstIndex == warriors.size() || secondIndex == warriors.size()) {
        cerr << "Error: invalid battle between " << firstName << " and "
             << secondName << endl;
        return;
    }

    //references so strength updates modify vector directly
    Warrior& firstWarrior = warriors[firstIndex];
    Warrior& secondWarrior = warriors[secondIndex];

    //follow assignment battle rules
    if (firstWarrior.strength == 0 && secondWarrior.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }

    else if (firstWarrior.strength == 0) {
        cout << "He's dead, " << secondWarrior.name << endl;
    }

    else if (secondWarrior.strength == 0) {
        cout << "He's dead, " << firstWarrior.name << endl;
    }

    else if (firstWarrior.strength == secondWarrior.strength) {
        firstWarrior.strength = 0;
        secondWarrior.strength = 0;
        cout << "Mutual Annihilation: " << firstWarrior.name << " and "
             << secondWarrior.name << " die at each other's hands" << endl;
    }

    else if (firstWarrior.strength > secondWarrior.strength) {
        firstWarrior.strength -= secondWarrior.strength;
        secondWarrior.strength = 0;
        cout << firstWarrior.name << " defeats " << secondWarrior.name << endl;
    }

    else {
        secondWarrior.strength -= firstWarrior.strength;
        firstWarrior.strength = 0;
        cout << secondWarrior.name << " defeats " << firstWarrior.name << endl;
    }
}

void statusCommand(const vector<Warrior>& warriors) {
    //status output  
    cout << "There are: " << warriors.size() << " warriors" << endl;
    //ranged for loop to print each warrior 
    for (const Warrior& warrior : warriors) {
        cout << "Warrior: " << warrior.name
             << ", strength: " << warrior.strength << endl;
    }
}

size_t findWarrior(const vector<Warrior>& warriors, const string& name) {
    //search data in vector
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].name == name) {
            return index;
        }
    }
    //if not found, return size
    return warriors.size();
}
