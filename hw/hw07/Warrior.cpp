/*
 Pragun Damani: pd2752
 Warrior.cpp
 Spring 2026
 */

#include "Warrior.h"
#include "Noble.h"

#include <iostream>

using namespace std;

namespace WarriorCraft {
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
        strength *= (1 - ratio);
    }

    void Warrior::die() {
        strength = 0;
    }

    ostream& operator<<(ostream& os, const Warrior& rhs) {
        os << '\t' << rhs.name << ": " << rhs.strength;
        return os;
    }
}
