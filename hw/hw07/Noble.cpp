/*
 Pragun Damani: pd2752
 Noble.cpp
 Spring 2026
 */

#include "Noble.h"
#include "Warrior.h"

#include <iostream>

using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name) : name(name), dead(false) {}

    const string& Noble::getName() const {
        return name;
    }

    bool Noble::hire(Warrior& warrior) {
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

    ostream& operator<<(ostream& os, const Noble& rhs) {
        os << rhs.name << " has an army of " << rhs.army.size();
        for (const Warrior* warrior : rhs.army) {
            os << '\n' << *warrior;
        }
        return os;
    }
}
