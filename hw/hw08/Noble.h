/*
 Pragun Damani: pd2752
 Noble.h
 Spring 2026
 */

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Protector;

    class Noble {
    friend std::ostream& operator<<(std::ostream& os, const Noble& rhs);

    public:
        Noble(const std::string& name);
        virtual ~Noble();

        const std::string& getName() const;
        bool isAlive() const;
        void battle(Noble& opponent);

    protected:
        void setDead();

    private:
        //pure virtuals for derived classes
        virtual double getStrength() const = 0;
        virtual void defend() const = 0;
        virtual void winsAgainst(double loserStrength) = 0;
        virtual void loses() = 0;
        virtual void display(std::ostream& os) const = 0;

        std::string name;
        bool alive;
    };

    class Lord : public Noble {
    public:
        Lord(const std::string& name);

        bool hires(Protector& protector);
        bool fires(Protector& protector);
        bool remove(Protector& protector);

    private:
        virtual double getStrength() const;
        virtual void defend() const;
        virtual void winsAgainst(double loserStrength);
        virtual void loses();
        virtual void display(std::ostream& os) const;

        size_t findProtector(const Protector& protector) const;

        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(const std::string& name, double strength);

    private:
        virtual double getStrength() const;
        virtual void defend() const;
        virtual void winsAgainst(double loserStrength);
        virtual void loses();
        virtual void display(std::ostream& os) const;

        double strength;
    };

    std::ostream& operator<<(std::ostream& os, const Noble& rhs);
}

#endif
