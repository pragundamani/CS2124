/*
 Pragun Damani: pd2752
 hw03.cpp
 Spring 2026
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Warrior {
friend ostream& operator<<(ostream& os, const Warrior& rhs);
private:
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& rhs) {
            os << "weapon: " << rhs.name << ", " << rhs.strength;
            return os;
        }
public:
    //creates weapon with name + initial strength
    Weapon(const string& name, int strength) :name(name),strength(strength){ }
    int getStrength() const { return strength; }
    void setStrength(int newStrength) {
        strength = newStrength;
    }
private:
    string name;
    int strength;
    };
public:
    Warrior(const string& name, const string& weaponName, int strength)
        :name(name),weapon(weaponName,strength) {}
    const string& getName() const {return name;}
    int getStrength() const {return weapon.getStrength();}
    bool isDead() const {return getStrength() == 0;}
    void battle(Warrior& opponent);
private:
    void setStrength(int newStrength) {weapon.setStrength(newStrength);}
    string name;
    Weapon weapon;
};

//output format for warrior status line
ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << "Warrior: " << rhs.name << ", " << rhs.weapon;
    return os;
}

void Warrior::battle(Warrior& opponent) {
    //follow assignment battle rules
    if (isDead() && opponent.isDead()) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (isDead()) {
        cout << "He's dead, " << opponent.getName() << endl;
    }
    else if (opponent.isDead()) {
        cout << "He's dead, " << getName() << endl;
    }
    else if (getStrength() == opponent.getStrength()) {
        setStrength(0);
        opponent.setStrength(0);
        cout << "Mutual Annihilation: " << getName() << " and "
             << opponent.getName() << " die at each other's hands" << endl;
    }
    else if (getStrength() > opponent.getStrength()) {
        setStrength(getStrength() - opponent.getStrength());
        opponent.setStrength(0);
        cout << getName() << " defeats " << opponent.getName() << endl;
    }
    else {
        opponent.setStrength(opponent.getStrength() - getStrength());
        setStrength(0);
        cout << opponent.getName() << " defeats " << getName() << endl;
    }
}

  //prototypes
void commands(ifstream& warriorStream, vector<Warrior>& warriors);
void warriorCommand(vector<Warrior>& warriors, const string& warriorName,
                    const string& weaponName, int weaponStrength);
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
}

void commands(ifstream& warriorStream, vector<Warrior>& warriors) {
    string command; //temp var for each command
    while (warriorStream >> command) {
        //read fields that belong current command
        if (command == "Warrior") {
            string warriorName;
            string weaponName;
            int weaponStrength;
            warriorStream >> warriorName >> weaponName >> weaponStrength;
            warriorCommand(warriors, warriorName, weaponName, weaponStrength);
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

void warriorCommand(vector<Warrior>& warriors, const string& warriorName,
                    const string& weaponName, int weaponStrength) {
    //no duplicates
    if (findWarrior(warriors, warriorName) != warriors.size()) {
        cerr << "Error: warrior " << warriorName << " already exists" << endl;
        return;
    }
    //create new warrior and add to vector
    warriors.emplace_back(warriorName, weaponName, weaponStrength);
}

void battleCommand(vector<Warrior>& warriors, const string& firstName,
                   const string& secondName) {
    //first output for battle
    cout << firstName << " battles " << secondName << endl;

    //look up both warriors by name
    const size_t firstIndex = findWarrior(warriors, firstName);
    const size_t secondIndex = findWarrior(warriors, secondName);
    if (firstIndex == warriors.size() || secondIndex == warriors.size()) {
        cerr << "Error: invalid battle between " << firstName << " and "
             << secondName << endl;
        return;
    }
    warriors[firstIndex].battle(warriors[secondIndex]);
}

void statusCommand(const vector<Warrior>& warriors) {
    //status output
    cout << "There are: " << warriors.size() << " warriors" << endl;
    //ranged for loop to print each warrior
    for (const Warrior& warrior : warriors) {
        cout << warrior << endl;
    }
}

size_t findWarrior(const vector<Warrior>& warriors, const string& name) {
    //search data in vector
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].getName() == name) {
            return index;
        }
    }
    //if not found return size
    return warriors.size();
}
