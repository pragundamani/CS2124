/*
 Pragun Damani: pd2752
 hw07_single.cpp
 Spring 2026
 */

// Comment out these two includes for the single file solution
/*#include "Noble.h"
#include "Warrior.h"
*/

#include <iostream>  
#include <vector>   
#include <string>                    

using namespace std;

// Comment out this "using namespace" for the single file solution
//using namespace WarriorCraft;

class Noble;

class Warrior {
friend ostream& operator<<(ostream& os, const Warrior& rhs);
public:
    Warrior(const string& name, double strength);

    const string& getName() const;
    double getStrength() const;
    bool isHired() const;

    void setEmployer(Noble* noble);
    void runaway();
    void loseStrength(double ratio);
    void die();

private:
    string name;
    double strength;
    Noble* employer;
};

class Noble {
friend ostream& operator<<(ostream& os, const Noble& rhs);
public:
    Noble(const string& name);

    const string& getName() const;
    bool hire(Warrior& warrior);
    bool fire(Warrior& warrior);
    bool remove(Warrior& warrior);
    void battle(Noble& opponent);
    bool employs(const Warrior& warrior) const;

private:
    double getArmyStrength() const;
    void killArmy();
    void reduceArmyStrength(double ratio);
    size_t findWarrior(const Warrior& warrior) const;

    string name;
    vector<Warrior*> army;
    bool dead;
};

//prototype

ostream& operator<<(ostream& os, const Warrior& rhs);
ostream& operator<<(ostream& os, const Noble& rhs);

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

Warrior::Warrior(const string& name, double strength)
    : name(name), strength(strength), employer(nullptr) {}

const string& Warrior::getName() const {
    return name;
}

double Warrior::getStrength() const {
    return strength;
}

bool Warrior::isHired() const {
    return employer != nullptr;
}

void Warrior::setEmployer(Noble* noble) {
    employer = noble;
}

void Warrior::runaway() {
    if (!isHired()) {
        return;
    }

    Noble* noble = employer;
    cout << name << " flees in terror, abandoning his lord, "
         << noble->getName() << endl;
    noble->remove(*this);
}

void Warrior::loseStrength(double ratio) {
    //reduce winner strength by ratio
    strength *= (1 - ratio);
}

void Warrior::die() {
    strength = 0;
}

Noble::Noble(const string& name) : name(name), dead(false) {}

const string& Noble::getName() const {
    return name;
}

bool Noble::hire(Warrior& warrior) {
    //fail if dead or employed
    if (dead || warrior.isHired()){
        cout << name << " failed to hire " << warrior.getName() << endl;
        return false;
    }

    army.push_back(&warrior);
    warrior.setEmployer(this);
    return true;
}

bool Noble::fire(Warrior& warrior) {
    const size_t index = findWarrior(warrior);
    //fail if dead or not in army
    if (dead || index == army.size()){
        cout << name << " failed to fire " << warrior.getName() << endl;
        return false;
    }

    cout << warrior.getName() << ", you don't work for me anymore ! -- "
         << name << '.' << endl;
    return remove(warrior);
}

bool Noble::remove(Warrior& warrior) {
    const size_t index = findWarrior(warrior);
    if (index == army.size()) {
        return false;
    }

    warrior.setEmployer(nullptr);
    //shift left keep order
    for (size_t i = index; i + 1 < army.size(); ++i) {
        army[i] = army[i + 1];
    }
    army.pop_back();
    return true;
}

void Noble::battle(Noble& opponent) {
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
                 << opponent.name << " die at each other's hands" << endl;
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

bool Noble::employs(const Warrior& warrior) const {
    return findWarrior(warrior) != army.size();
}

double Noble::getArmyStrength() const {
    double total = 0;
    for (const Warrior* warrior : army) {
        total += warrior->getStrength();
    }
    return total;
}

void Noble::killArmy() {
    for (Warrior* warrior : army) {
        warrior->die();
    }
}

void Noble::reduceArmyStrength(double ratio) {
    for (Warrior* warrior : army) {
        warrior->loseStrength(ratio);
    }
}

size_t Noble::findWarrior(const Warrior& warrior) const {
    for (size_t i = 0; i < army.size(); ++i) {
        if (army[i] == &warrior){
            return i;
        }
    }
    return army.size();
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
