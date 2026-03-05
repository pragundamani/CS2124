/*
 Pragun Damani: pd2752
 hw05.cpp
 Spring 2026
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Warrior {
friend ostream& operator<<(ostream& os, const Warrior& rhs);

public:
    Warrior(const string& name, double strength)
        : name(name), strength(strength), employed(false) {}

    const string& getName() const {return name;}
    double getStrength() const {return strength;}
    bool isEmployed() const {return employed;}

    void hire() {employed = true;}
    void fire() {employed = false;}

    void reduceStrength(double ratio) {
        //reduce winner strength by ratio
        strength *= (1 - ratio);
    }

    void die() {strength = 0;}

private:
    string name;
    double strength;
    bool employed;
};

class Noble {
friend ostream& operator<<(ostream& os, const Noble& rhs);

public:
    Noble(const string& name) : name(name), dead(false) {}

    const string& getName() const {return name;}

    bool hire(Warrior& warrior) {
        //fail if dead or employed
        if (dead || warrior.isEmployed()){
            cout << name << " failed to hire " << warrior.getName() << endl;
            return false;
        }
        army.push_back(&warrior);
        warrior.hire();
        return true;
    }

    bool fire(Warrior& warrior) {
        const size_t index = findWarrior(warrior);
        //fail if dead or not in army
        if (dead || index == army.size()){
            cout << name << " failed to fire " << warrior.getName() << endl;
            return false;
        }

        cout << warrior.getName() << ", you don't work for me any more! -- "
             << name << "." << endl;
        warrior.fire();

        //shift left keep order
        for (size_t i = index; i + 1 < army.size(); ++i) {
            army[i] = army[i + 1];
        }
        army.pop_back();
        return true;
    }

    void battle(Noble& opponent) {
        cout << name << " battles " << opponent.name << endl;

        if (dead && opponent.dead){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        }
        else if (dead){
            cout << "He's dead, " << opponent.name << endl;
        }
        else if (opponent.dead){
            cout << "He's dead, " << name << endl;
        }
        else {
            const double myStrength = getArmyStrength();
            const double opponentStrength = opponent.getArmyStrength();

            if (myStrength == opponentStrength){
                cout << "Mutual Annihilation: " << name << " and "
                     << opponent.name
                     << " die at each other's hands" << endl;
                dead = true;
                opponent.dead = true;
                killArmy();
                opponent.killArmy();
            }
            else if (myStrength > opponentStrength){
                cout << name << " defeats " << opponent.name << endl;
                const double ratio = opponentStrength / myStrength;
                reduceArmyStrength(ratio);
                opponent.killArmy();
                opponent.dead = true;
            }
            else {
                cout << opponent.name << " defeats " << name << endl;
                const double ratio = myStrength / opponentStrength;
                opponent.reduceArmyStrength(ratio);
                killArmy();
                dead = true;
            }
        }
    }

    bool employs(const Warrior& warrior) const {
        return findWarrior(warrior) != army.size();
    }

private:
    double getArmyStrength() const {
        double total = 0;
        for (const Warrior* warrior : army) {
            total += warrior->getStrength();
        }
        return total;
    }

    void killArmy() {
        for (Warrior* warrior : army) {
            warrior->die();
        }
    }

    void reduceArmyStrength(double ratio) {
        for (Warrior* warrior : army) {
            warrior->reduceStrength(ratio);
        }
    }

    size_t findWarrior(const Warrior& warrior) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &warrior){
                return i;
            }
        }
        return army.size();
    }

    string name;
    vector<Warrior*> army;
    bool dead;
};

//prototypes
void commands(ifstream& input, vector<Noble*>& nobles,
              vector<Warrior*>& warriors);
void nobleCommand(vector<Noble*>& nobles, const string& nobleName);
void warriorCommand(vector<Warrior*>& warriors, const string& warriorName,
                    double strength);
void hireCommand(const vector<Noble*>& nobles, const vector<Warrior*>& warriors,
                 const string& nobleName, const string& warriorName);
void fireCommand(const vector<Noble*>& nobles, const vector<Warrior*>& warriors,
                 const string& nobleName, const string& warriorName);
void battleCommand(const vector<Noble*>& nobles, const string& nobleName1,
                   const string& nobleName2);
void statusCommand(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
void clearCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors);
Noble* findNoble(const vector<Noble*>& nobles, const string& name);
Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name);

int main() {
    vector<Noble*> nobles;
    vector<Warrior*> warriors;

    ifstream input("nobleWarriors.txt");
    if (!input) {
        cerr << "Error: could not open nobleWarriors.txt" << endl;
        return 1;
    }

    //read and execute commands in order
    commands(input, nobles, warriors);

    //cleanup if file does not end in Clear
    clearCommand(nobles, warriors);
}

void commands(ifstream& input, vector<Noble*>& nobles,
              vector<Warrior*>& warriors) {
    string command;
    while (input >> command) {
        if (command == "Noble") {
            string nobleName;
            input >> nobleName;
            nobleCommand(nobles, nobleName);
        }

        else if (command == "Warrior") {
            string warriorName;
            double strength = 0;
            input >> warriorName >> strength;
            warriorCommand(warriors, warriorName, strength);
        }

        else if (command == "Hire") {
            string nobleName;
            string warriorName;
            input >> nobleName >> warriorName;
            hireCommand(nobles, warriors, nobleName, warriorName);
        }

        else if (command == "Fire") {
            string nobleName;
            string warriorName;
            input >> nobleName >> warriorName;
            fireCommand(nobles, warriors, nobleName, warriorName);
        }

        else if (command == "Battle") {
            string nobleName1;
            string nobleName2;
            input >> nobleName1 >> nobleName2;
            battleCommand(nobles, nobleName1, nobleName2);
        }

        else if (command == "Status") {
            statusCommand(nobles, warriors);
        }

        else if (command == "Clear") {
            clearCommand(nobles, warriors);
        }
    }
}

void nobleCommand(vector<Noble*>& nobles, const string& nobleName) {
    //duplicate noble names are not allowed
    if (findNoble(nobles, nobleName)) {
        cerr << "Error: noble already exists: " << nobleName << endl;
        return;
    }

    nobles.push_back(new Noble(nobleName));
}

void warriorCommand(vector<Warrior*>& warriors, const string& warriorName,
                    double strength) {
    //duplicate warrior names are not allowed
    if (findWarrior(warriors, warriorName)) {
        cerr << "Error: warrior already exists: " << warriorName << endl;
        return;
    }

    warriors.push_back(new Warrior(warriorName, strength));
}

void hireCommand(const vector<Noble*>& nobles, const vector<Warrior*>& warriors,
                 const string& nobleName, const string& warriorName) {
    Noble* noble = findNoble(nobles, nobleName);
    Warrior* warrior = findWarrior(warriors, warriorName);

    if (!noble) {
        cerr << "Attempting to hire using unknown noble: " << nobleName << endl;
    }
    else if (!warrior) {
        cerr << "Attempting to hire using unknown warrior: " << warriorName
             << endl;
    }
    else {
        noble->hire(*warrior);
    }
}

void fireCommand(const vector<Noble*>& nobles, const vector<Warrior*>& warriors,
                 const string& nobleName, const string& warriorName) {
    Noble* noble = findNoble(nobles, nobleName);
    Warrior* warrior = findWarrior(warriors, warriorName);

    if (!noble) {
        cerr << "Attempting to fire using unknown noble: " << nobleName << endl;
    }
    else if (!warrior) {
        cerr << "Attempting to fire using unknown warrior: " << warriorName
             << endl;
    }
    else if (!noble->employs(*warrior)) {
        cerr << nobleName << " does not have " << warriorName
             << " in the army" << endl;
    }
    else {
        noble->fire(*warrior);
    }
}

void battleCommand(const vector<Noble*>& nobles, const string& nobleName1,
                   const string& nobleName2) {
    Noble* firstNoble = findNoble(nobles, nobleName1);
    Noble* secondNoble = findNoble(nobles, nobleName2);

    if (!firstNoble || !secondNoble) {
        cerr << "Attempting a battle with unknown noble" << endl;
        return;
    }

    firstNoble->battle(*secondNoble);
}

void statusCommand(const vector<Noble*>& nobles, const vector<Warrior*>& warriors) {
    cout << "Status" << endl;
    cout << "======" << endl;

    cout << "Nobles:" << endl;
    if (nobles.empty()) {
        cout << "NONE" << endl;
    }
    else {
        for (const Noble* noble : nobles) {
            cout << *noble << endl;
        }
    }

    cout << endl;
    cout << "Unemployed Warriors:" << endl;
    bool hasUnemployedWarrior = false;
    for (const Warrior* warrior : warriors) {
        if (!warrior->isEmployed()) {
            cout << *warrior << endl;
            hasUnemployedWarrior = true;
        }
    }

    if (!hasUnemployedWarrior) {
        cout << "NONE" << endl;
    }
}

void clearCommand(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    for (Noble* noble : nobles) {
        delete noble;
    }
    nobles.clear();

    for (Warrior* warrior : warriors) {
        delete warrior;
    }
    warriors.clear();
}

Noble* findNoble(const vector<Noble*>& nobles, const string& name) {
    for (Noble* noble : nobles) {
        if (noble->getName() == name) {
            return noble;
        }
    }
    return nullptr;
}

Warrior* findWarrior(const vector<Warrior*>& warriors, const string& name) {
    for (Warrior* warrior : warriors) {
        if (warrior->getName() == name) {
            return warrior;
        }
    }
    return nullptr;
}

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << '\t' << rhs.name << ": " << rhs.strength;
    return os;
}

ostream& operator<<(ostream& os, const Noble& rhs) {
    os << rhs.name << " has an army of " << rhs.army.size();
    for (const Warrior* warrior : rhs.army) {
        os << '\n' << *warrior;
    }
    return os;
}
