/*
 Pragun Damani: pd2752
 Noble.h
 Spring 2026
 */

#ifndef NOBLE_H
#define NOBLE_H

#include <iosfwd>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;

    class Noble {
    friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);
    public:
        Noble(const std::string& name);

        const std::string& getName() const;
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

        std::string name;
        std::vector<Warrior*> army;
        bool dead;
    };

    std::ostream& operator<<(std::ostream& os, const Noble& rhs);
}

#endif
