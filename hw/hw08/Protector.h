/*
 Pragun Damani: pd2752
 Protector.h
 Spring 2026
 */

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <string>

namespace WarriorCraft {
    class Lord;

    class Protector {
    friend std::ostream& operator<<(std::ostream& os, const Protector& rhs);

    public:
        Protector(const std::string& name, double strength);
        virtual ~Protector();

        const std::string& getName() const;
        double getStrength() const;
        bool isHired() const;
        bool isAlive() const;
        void runaway();

    protected:
        const std::string& getLordName() const;

    private:
        //protector methods
        virtual void defend() const = 0;
        virtual void display(std::ostream& os) const;
        void setStrength(double newStrength);
        void setLord(Lord* newLord);

        std::string name;
        double strength;
        Lord* lord;

        friend class Lord;
    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string& name, double strength);

    private:
        virtual void defend() const;
    };

    class Warrior : public Protector {
    public:
        Warrior(const std::string& name, double strength);
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string& name, double strength);

    private:
        virtual void defend() const;
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string& name, double strength);

    private:
        virtual void defend() const;
    };

    std::ostream& operator<<(std::ostream& os, const Protector& rhs);
}

#endif
