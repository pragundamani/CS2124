/*
 Pragun Damani pd2752
 hw08.cpp
 Spring 2026
 */

#include "Noble.h"
#include "Protector.h"

#include <iostream>

using namespace std;
using namespace WarriorCraft;

int main()
{
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);

    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "\n==========\n";
    joe.battle(randy);
    joe.battle(sam);
    janet.battle(barclay);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    sam.hires(thora);
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    samantha.runaway();
    sam.fires(thora);
    joe.battle(barclay);

    cout << "\n==========\nNobles: \n"
         << sam << endl
         << randy << endl
         << janet << endl
         << barclay << endl
         << joe << endl
         << "==========\n";
}
