/*
 Pragun Damani: pd2752
 hw03.cpp
 Spring 2026
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& rhs);

private:
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& rhs) {
            os << "weapon: " << rhs.name << ", " << rhs.strength;
            return os;
        }

    public:
        Weapon(const string& name, int strength)
            : name(name), strength(strength) {}

        int getStrength() const { return strength; }
        void setStrength(int newStrength) { strength = newStrength; }

    private:
        string name;
        int strength;
    };

public:
    Warrior(const string& name, const string& weaponName, int strength)
        : name(name), weapon(weaponName, strength) {}

    const string& getName() const { return name; }
    int getStrength() const { return weapon.getStrength(); }
    bool isDead() const { return getStrength() == 0; }
    void battle(Warrior& opponent);

private:
    void setStrength(int newStrength) { weapon.setStrength(newStrength); }

    string name;
    Weapon weapon;
};

ostream& operator<<(ostream& os, const Warrior& rhs) {
    os << "Warrior: " << rhs.name << ", " << rhs.weapon;
    return os;
}

void Warrior::battle(Warrior& opponent) {
    //battle optiosn
    if (this->isDead() && opponent.isDead()) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (this->isDead()) {
        cout << "He's dead, " << opponent.getName() << endl;
    }
    else if (opponent.isDead()) {
        cout << "He's dead, " << this->getName() << endl;
    }
    else if (this->getStrength() == opponent.getStrength()) {
        this->setStrength(0);
        opponent.setStrength(0);
        cout << "Mutual Annihilation: " << this->getName() << " and "
             << opponent.getName() << " die at each other's hands" << endl;    
    }
    else if (this->getStrength() > opponent.getStrength()) {
        this->setStrength(this->getStrength() - opponent.getStrength());
        opponent.setStrength(0);
        cout << this->getName() << " defeats " << opponent.getName() << endl;
    }
    else {
        opponent.setStrength(opponent.getStrength() - this->getStrength());
        this->setStrength(0);
        cout << opponent.getName() << " defeats " << this->getName() << endl;
    }
}

class WarriorCollection {
public:
    void processCommands(istream& warriorStream) {
        string command;
        while (warriorStream >> command) {
            if (command == "Warrior") {
                string warriorName;
                string weaponName;
                int weaponStrength;
                warriorStream >> warriorName >> weaponName >> weaponStrength;
                addWarrior(warriorName, weaponName, weaponStrength);
            }

            else if (command == "Battle") {
                string firstName;
                string secondName;
                warriorStream >> firstName >> secondName;
                battleByName(firstName, secondName);
            }

            else if (command == "Status") {
                status();
            }
        }
    }

private:
    void addWarrior(const string& warriorName, const string& weaponName,
                    int weaponStrength) {
        //duplicate warrior name not allowed
        if (this->findWarrior(warriorName) != this->warriors.size()) {
            cerr << "Error: warrior " << warriorName << " already exists" << endl;
            return;
        }
        this->warriors.emplace_back(warriorName, weaponName, weaponStrength);
    }

    void battleByName(const string& firstName, const string& secondName) {
        cout << firstName << " battles " << secondName << endl;

        const size_t firstIndex = this->findWarrior(firstName);
        const size_t secondIndex = this->findWarrior(secondName);
        if (firstIndex == this->warriors.size() ||
            secondIndex == this->warriors.size()) {
            cerr << "Error: invalid battle between " << firstName
                 << " and " << secondName << endl;
            return;
        }
        this->warriors[firstIndex].battle(this->warriors[secondIndex]);
    }

    void status() const {
        cout << "There are: " << this->warriors.size() << " warriors" << endl;
        for (const Warrior& warrior : this->warriors) {
            cout << warrior << endl;
        }
    }

    size_t findWarrior(const string& name) const {
        for (size_t index = 0; index < this->warriors.size(); ++index) {
            if (this->warriors[index].getName() == name) {
                return index;
            }
        }
        return this->warriors.size();
    }

    vector<Warrior> warriors;
};

int main() {
    WarriorCollection warriorCollection;
    ifstream warriorStream("warriors.txt");

    if (!warriorStream) {
        cerr << "Error: could not open warriors.txt" << endl;
        return 1;
    }

    warriorCollection.processCommands(warriorStream);
}//:wq
