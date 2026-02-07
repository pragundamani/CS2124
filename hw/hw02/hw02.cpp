/*
Name: [Your Name]
Assignment: hw02 - functions, structs, vectors
Course: Object Oriented Programming Spring 2026 - NYU
File: hw02.cpp
Purpose: Battle simulator using functions, structs, vectors, and file I/O.

Summary of required behavior:
- Read commands from "warriors.txt" (do not prompt user for filename).
- Commands:
  - Warrior <name> <strength>: add a new warrior (unique names only).
  - Battle <name1> <name2>: resolve a battle and print results.
  - Status: print count and list of all warriors with strengths.
- Execute commands in order as they are read.
- Output formatting should match the assignment sample exactly for normal cases.
- Error cases:
  - Duplicate Warrior name: do not add; print an error message.
  - Battle with undefined warrior(s): do not battle; print an error message.

Battle rules:
- Each warrior has name and strength.
- If both warriors are dead (strength 0):
  - Print: "Oh, NO! They're both dead! Yuck!"
- If one is dead and the other alive:
  - Print: "He's dead, <living warrior name>"
- If both alive:
  - Equal strength: both strengths become 0; print:
    "Mutual Annihilation: <name1> and <name2> die at each other's hands"
  - Unequal strength: stronger wins, weaker becomes 0, winner loses amount
    equal to weaker's strength; print:
    "<winner> defeats <loser>"

Implementation requirements / style notes:
- Use structs (no classes, no constructors, no data hiding).
- Use functions and function prototypes so main appears first.
- Use vectors to store warriors.
- Keep lines <= 80 characters, good indentation, good naming.
- Include comments for known issues (if any).

Due date: Feb 9, 2026 11:59 PM
*/

// Intentionally left incomplete per instructions.
