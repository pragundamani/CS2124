/*
 Pragun Damani: pd2752
 Warrior.h
 Spring 2026
 */

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iosfwd>
#include <string>

namespace WarriorCraft {
    class Noble;

    class Warrior {
    friend std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
    public:
        Warrior(const std::string& name, double strength);

        const std::string& getName() const;
        double getStrength() const;
        bool isHired() const;

        void setEmployer(Noble* noble);
        void runaway();
        void loseStrength(double ratio);
        void die();

    private:
        std::string name;
        double strength;
        Noble* employer;
    };

    std::ostream& operator<<(std::ostream& os, const Warrior& rhs);
}

#endif
