/*
 Pragun Damani: pd2752
 Noble.cpp
 Spring 2026
 */

#include "Noble.h"
#include "Protector.h"

#include <iostream>

using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& name) : name(name), alive(true) {}

    Noble::~Noble() {}

    const string& Noble::getName() const {return name;}

    bool Noble::isAlive() const {return alive;}

    void Noble::setDead() {alive = false;}

    void Noble::battle(Noble& opponent) {
        cout << getName() << " battles " << opponent.getName() << endl;

        if (!isAlive() && !opponent.isAlive()) {
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            return;
        }

        if (!isAlive()) {
            opponent.defend();
            cout << "He's dead " << opponent.getName() << endl;
            return;
        }

        if (!opponent.isAlive()) {
            defend();
            cout << "He's dead " << getName() << endl;
            return;
        }

        defend();
        opponent.defend();

        const double myStrength = getStrength();
        const double opponentStrength = opponent.getStrength();

        if (myStrength == opponentStrength) {
            cout << "Mutual Annihilation: " << getName() << " and "
                 << opponent.getName() << " die at each other's hands" << endl;
            loses();
            opponent.loses();
        }
        else if (myStrength > opponentStrength) {
            cout << getName() << " defeats " << opponent.getName() << endl;
            winsAgainst(opponentStrength);
            opponent.loses();
        }
        else {
            cout << opponent.getName() << " defeats " << getName() << endl;
            opponent.winsAgainst(myStrength);
            loses();
        }
    }

    Lord::Lord(const string& name) : Noble(name) {}

    bool Lord::hires(Protector& protector) {
        //check sutiable hire
        if (!isAlive() || protector.isHired() || !protector.isAlive()) {
            cout << getName() << " failed to hire " << protector.getName() << endl;
            return false;
        }

        army.push_back(&protector);
        protector.setLord(this);
        return true;
    }

    bool Lord::fires(Protector& protector) {
        const size_t index = findProtector(protector);
        if (index == army.size()) {
            cout << getName() << " failed to fire " << protector.getName() << endl;
            return false;
        }

        cout << protector.getName() << ", you don't work for me anymore ! -- "
             << getName() << '.' << endl;
        return remove(protector);
    }

    bool Lord::remove(Protector& protector) {
        const size_t index = findProtector(protector);
        if (index == army.size()) {
            return false;
        }

        protector.setLord(nullptr);
        //preserve army order
        for (size_t i = index; i + 1 < army.size(); ++i) {
            army[i] = army[i + 1];
        }
        army.pop_back();
        return true;
    }

    double Lord::getStrength() const {
        double total = 0;
        for (size_t i = 0; i < army.size(); ++i) {
            total += army[i]->getStrength();
        }
        return total;
    }

    void Lord::defend() const {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->defend();
        }
    }

    void Lord::winsAgainst(double loserStrength) {
        const double ratio = loserStrength / getStrength();
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(army[i]->getStrength() * (1 - ratio));
        }
    }

    void Lord::loses() {
        for (size_t i = 0; i < army.size(); ++i) {
            army[i]->setStrength(0);
        }
        setDead();
    }

    void Lord::display(ostream& os) const {
        os << getName() << " has an army of size: " << army.size();
        for (size_t i = 0; i < army.size(); ++i) {
            os << '\n' << *army[i];
        }
    }

    size_t Lord::findProtector(const Protector& protector) const {
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &protector) {
                return i;
            }
        }
        return army.size();
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(
            const string& name, double strength)
        : Noble(name), strength(strength) {}

    double PersonWithStrengthToFight::getStrength() const {return strength;}

    void PersonWithStrengthToFight::defend() const {
        if (strength > 0) {
            cout << "Ugh!" << endl;
        }
    }

    void PersonWithStrengthToFight::winsAgainst(double loserStrength) {
        strength -= loserStrength;
    }

    void PersonWithStrengthToFight::loses() {
        strength = 0;
        setDead();
    }

    void PersonWithStrengthToFight::display(ostream& os) const {
        os << getName() << " has strength: " << strength;
    }

    ostream& operator<<(ostream& os, const Noble& rhs) {
        rhs.display(os);
        return os;
    }
}
