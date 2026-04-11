/*
 Pragun Damani: pd2752
 Protector.cpp
 Spring 2026
 */

#include "Protector.h"
#include "Noble.h"

#include <iostream>

using namespace std;

namespace WarriorCraft {
    Protector::Protector(const string& name, double strength)
        : name(name), strength(strength), lord(nullptr) {}

    Protector::~Protector() {}

    const string& Protector::getName() const {return name;}

    double Protector::getStrength() const {return strength;}

    bool Protector::isHired() const {return lord != nullptr;}

    bool Protector::isAlive() const {return strength > 0;}

    void Protector::runaway() {
        if (!isHired()) {
            return;
        }

        Lord* formerLord = lord;
        cout << getName() << " flees in terror, abandoning his lord, "
             << formerLord->getName() << endl;
        formerLord->remove(*this);
    }

    void Protector::display(ostream& os) const {
        os << '\t' << getName() << " has strength " << getStrength();
    }

    void Protector::setStrength(double newStrength) {strength = newStrength;}

    void Protector::setLord(Lord* newLord) {lord = newLord;}

    const string& Protector::getLordName() const {return lord->getName();}

    Wizard::Wizard(const string& name, double strength)
        : Protector(name, strength) {}

    void Wizard::defend() const {
        if (isAlive()) {
            cout << "POOF!" << endl;
        }
    }

    Warrior::Warrior(const string& name, double strength)
        : Protector(name, strength) {}

    Archer::Archer(const string& name, double strength)
        : Warrior(name, strength) {}

    void Archer::defend() const {
        if (isAlive()) {
            cout << "TWANG!  " << getName()
                 << " says: Take that in the name of my lord, "
                 << getLordName() << endl;
        }
    }

    Swordsman::Swordsman(const string& name, double strength)
        : Warrior(name, strength) {}

    void Swordsman::defend() const {
        if (isAlive()) {
            cout << "CLANG!  " << getName()
                 << " says: Take that in the name of my lord, "
                 << getLordName() << endl;
        }
    }

    ostream& operator<<(ostream& os, const Protector& rhs) {
        rhs.display(os);
        return os;
    }
}
