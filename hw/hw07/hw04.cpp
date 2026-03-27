/*
 Pragun Damani: pd2752
 hw04_start.cpp
 Spring 2026
 */

#include <iostream>
#include <vector>
#include <string>
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
        size_t index = findWarrior(warrior);
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

int main()
{
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
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
