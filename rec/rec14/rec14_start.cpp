/*
  rec14_starter code
 */

#include <algorithm> // max
#include <climits>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

// Node type for the linked list
struct Node {
  int data = 0;
  Node *next = nullptr;
};

// Node type for the ternary tree
struct TNode {
  int data = 0;
  TNode *left = nullptr;
  TNode *mid = nullptr;
  TNode *right = nullptr;
};

/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node *headPtr);
void listClear(Node *&headPtr);
Node *listBuild(const vector<int> &vals);

//
// Your functions go here
//
//   Task 1 function:
//
Node *listSum(const Node *listOne, const Node *listTwo) {
  if (listOne == nullptr && listTwo == nullptr)
    return nullptr;
  int sum = 0;
  Node *one = nullptr;
  Node *two = nullptr;
  if (listOne != nullptr) {
    sum += listOne->data;
    one = listOne->next;
  }
  if (listTwo != nullptr) {
    sum += listTwo->data;
    two = listTwo->next;
  }
  // Node* result = new Node{sum, listSum(one,two)}
  Node *result = new Node;
  result->data = sum;
  result->next = listSum(one, two);
  return result;
}

//   Task 2 function
//
int treeMax(const TNode *root) {
  if (root == nullptr)
    throw invalid_argument("error");
  int res = root->data;
  if (root->right != nullptr)
    res = max(res, treeMax(root->right));
  if (root->left != nullptr)
    res = max(res, treeMax(root->left));
  if (root->mid != nullptr)
    res = max(res, treeMax(root->mid));
  return res;
}

//   Task 3 function:
bool palindrome(const char letters[], int letLen) {
  if (letLen > 1) {
    if (letters[0] == letters[letLen - 1]) {
      return palindrome(&letters[1], letLen - 2);
    }
    return false;
  }
  return true;
}

//   Task 4 function:
// bool parity(unsigned num, int numOnes = 0) {
bool parity(unsigned num) {
  if (num < 2) {
    if (num == 1)
      return false;
    return true;
  }
  if (num % 2 == 1)
    return !(parity(num / 2));
  return parity(num / 2);
  // return parity(num / 2, numOnes);
}

//   Task 5 function:
int towers(int i, char source, char target, char spare) {
  if (i == 0)
    return 0;
  // return 1 + towers(i - 1, spare, source, target) +
  // towers(i - 1, spare, target, source);
  return towers(i - 1, source, spare, target) + 1 +
         towers(i - 1, spare, target, source);
}

int main() {
  // We have provided some test code to save you time. Certainly feel
  // free to write more!

  // Task 1:
  cout << "\n==============\n#1: Testing listSum\n";
  Node *l1 = listBuild({2, 7, 1, 8});
  cout << "List (l1): ";
  listPrint(l1);

  Node *l2 = listBuild({9, 1, 4, 1});
  cout << "List (l2): ";
  listPrint(l2);

  Node *l3 = listBuild({3, 1, 4, 1, 5, 9});
  cout << "List (l3): ";
  listPrint(l3);

  cout << "The sum of l1 and l2: ";
  Node *l4 = listSum(l1, l2);
  listPrint(l4);

  cout << "The sum of l1 and l3: ";
  Node *l5 = listSum(l1, l3);
  listPrint(l5);

  cout << "The sum of l3 and l1: ";
  Node *l6 = listSum(l3, l1);
  listPrint(l6);

  listClear(l1);
  listClear(l2);
  listClear(l3);
  listClear(l4);
  listClear(l5);
  listClear(l6);

  // Task 2:
  cout << "\n==============\n"
       << "#2) Testing max of Tree.\n";
  // TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
  TNode a{1}, b{20}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
  cout << "treeMax(&f): " << treeMax(&f) << endl;

  // How do you keep this from crashing? try/catch! Here in main!
  try {
    cout << treeMax(nullptr) << endl;
  }

  catch (invalid_argument &e) {
    cout << e.what();
  }

  // Task 3:
  cout << "\n==============\n"
       << "#3) Testing palindrome\n";
  cout << boolalpha
       << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
       << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
       << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
       << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;

  // Task 4:
  cout << "\n==============\n"
       << "#4) Are there an even number of 1's in binary representation?\n";
  cout << boolalpha;
  for (int i = 0; i < 10; ++i) {
    cout << i << ": " << parity(i) << endl;
  }

  // Task 5:
  cout << "\n==============\n"
       << "#5) How many moves are required for various sized towers?";
  for (int i = 1; i < 30; ++i) {
    cout << "towers(" << i << ", 'a', 'b', 'c'): " << towers(i, 'a', 'b', 'c')
         << endl;
  }
}

//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node *headPtr) {
  const Node *curr = headPtr;
  while (curr != nullptr) {
    cout << curr->data << ' ';
    curr = curr->next;
  }
  cout << endl;
} // listPrint

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node *&headPtr) {
  while (headPtr) {
    Node *next = headPtr->next;
    delete headPtr;
    headPtr = next;
  }
} // listClear

// listBuild returns a list with the same values as in the vector.
Node *listBuild(const vector<int> &vals) {
  Node *result = nullptr;
  for (size_t index = vals.size(); index > 0; --index) {
    result = new Node{vals[index - 1], result};
  }
  return result;
} // listBuild
