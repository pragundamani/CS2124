/*
 Pragun Damani: pd2752
 polynomial.cpp
 Spring 2026
 */

#include "polynomial.h"

#include <iostream>
#include <vector>

using namespace std;

Polynomial::Polynomial() : head(new Node{0, nullptr}), degree(0) {}

Polynomial::Polynomial(const vector<int> &coef) : head(nullptr), degree(0) {
  if (coef.size() == 0) {
    head = new Node{0, nullptr};
    return;
  }

  size_t start = 0;
  while (start + 1 < coef.size() && coef[start] == 0) {
    ++start;
  }

  Node *tail = nullptr;
  for (size_t i = start; i < coef.size(); ++i) {
    Node *newNode = new Node{coef[i], nullptr};
    if (head == nullptr) {
      head = newNode;
    } else {
      tail->next = newNode;
    }
    tail = newNode;
  }

  degree = coef.size() - start - 1;

  while (degree > 0 && head != nullptr && head->coef == 0) {
    Node *oldHead = head;
    head = head->next;
    delete oldHead;
    --degree;
  }

  if (head == nullptr) {
    head = new Node{0, nullptr};
    degree = 0;
  }
}

Polynomial::Polynomial(const Polynomial &rhs) : head(nullptr), degree(0) {
  if (rhs.head != nullptr) {
    head = new Node{rhs.head->coef, nullptr};
    Node *tail = head;
    const Node *source = rhs.head->next;

    while (source != nullptr) {
      tail->next = new Node{source->coef, nullptr};
      tail = tail->next;
      source = source->next;
    }
  }
  degree = rhs.degree;
}

Polynomial::~Polynomial() {
  while (head != nullptr) {
    Node *oldHead = head;
    head = head->next;
    delete oldHead;
  }
}

Polynomial &Polynomial::operator=(const Polynomial &rhs) {
  if (this != &rhs) {
    while (head != nullptr) {
      Node *oldHead = head;
      head = head->next;
      delete oldHead;
    }

    if (rhs.head != nullptr) {
      head = new Node{rhs.head->coef, nullptr};
      Node *tail = head;
      const Node *source = rhs.head->next;

      while (source != nullptr) {
        tail->next = new Node{source->coef, nullptr};
        tail = tail->next;
        source = source->next;
      }
    }
    degree = rhs.degree;
  }
  return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &rhs) {
  Node *sumHead = nullptr;
  Node *sumTail = nullptr;

  const Node *longer = head;
  const Node *shorter = rhs.head;
  int diff = degree - rhs.degree;
  int newDegree = degree;

  if (rhs.degree > degree) {
    longer = rhs.head;
    shorter = head;
    diff = rhs.degree - degree;
    newDegree = rhs.degree;
  }

  for (int count = 0; count < diff; ++count) {
    Node *newNode = new Node{longer->coef, nullptr};
    if (sumHead == nullptr) {
      sumHead = newNode;
    } else {
      sumTail->next = newNode;
    }
    sumTail = newNode;
    longer = longer->next;
  }

  while (longer != nullptr && shorter != nullptr) {
    Node *newNode = new Node{longer->coef + shorter->coef, nullptr};
    if (sumHead == nullptr) {
      sumHead = newNode;
    } else {
      sumTail->next = newNode;
    }
    sumTail = newNode;
    longer = longer->next;
    shorter = shorter->next;
  }

  while (head != nullptr) {
    Node *oldHead = head;
    head = head->next;
    delete oldHead;
  }
  head = sumHead;
  degree = newDegree;

  while (degree > 0 && head != nullptr && head->coef == 0) {
    Node *oldHead = head;
    head = head->next;
    delete oldHead;
    --degree;
  }

  if (head == nullptr) {
    head = new Node{0, nullptr};
    degree = 0;
  }
  return *this;
}

int Polynomial::evaluate(int x) const {
  return eval(x);
}

int Polynomial::eval(int x) const {
  int result = 0;
  for (Node *curr = head; curr != nullptr; curr = curr->next) {
    result = result * x + curr->coef;
  }
  return result;
}

bool Polynomial::operator==(const Polynomial &rhs) const {
  if (degree != rhs.degree) {
    return false;
  }

  Node *left = head;
  Node *right = rhs.head;
  while (left != nullptr && right != nullptr) {
    if (left->coef != right->coef) {
      return false;
    }
    left = left->next;
    right = right->next;
  }
  return left == nullptr && right == nullptr;
}

bool Polynomial::operator!=(const Polynomial &rhs) const {
  return !(*this == rhs);
}

ostream &operator<<(ostream &os, const Polynomial &rhs) {
  if (rhs.head == nullptr) {
    return os << 0;
  }

  bool printedTerm = false;
  int exponent = rhs.degree;

  for (Polynomial::Node *curr = rhs.head; curr != nullptr;
       curr = curr->next, --exponent) {
    const int coef = curr->coef;
    if (coef == 0) {
      continue;
    }

    if (printedTerm) {
      os << (coef > 0 ? "+" : "-");
    } else if (coef < 0) {
      os << "-";
    }

    const int magnitude = coef < 0 ? -coef : coef;
    if (exponent == 0) {
      os << magnitude;
    } else {
      if (magnitude != 1) {
        os << magnitude;
      }
      os << "x";
      if (exponent != 1) {
        os << "^" << exponent;
      }
    }

    printedTerm = true;
  }

  if (!printedTerm) {
    os << 0;
  }

  return os;
}

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
  Polynomial result(lhs);
  result += rhs;
  return result;
}
