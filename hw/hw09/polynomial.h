/*
 Pragun Damani: pd2752
 polynomial.h
 Spring 2026
 */

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

class Polynomial {
  friend std::ostream &operator<<(std::ostream &os, const Polynomial &rhs);
  friend Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);

public:
  Polynomial();
  Polynomial(const std::vector<int> &coef);
  Polynomial(const Polynomial &rhs);
  ~Polynomial();

  Polynomial &operator=(const Polynomial &rhs);
  Polynomial &operator+=(const Polynomial &rhs);

  int evaluate(int x) const;
  int eval(int x) const;

  bool operator==(const Polynomial &rhs) const;
  bool operator!=(const Polynomial &rhs) const;

private:
  struct Node {
    int coef;
    Node *next;
  };

  Node *head;
  int degree;
};

std::ostream &operator<<(std::ostream &os, const Polynomial &rhs);
Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs);

#endif
