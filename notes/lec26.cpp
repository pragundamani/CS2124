#include <iostream>
using namespace std;

void towers(int n, char start, char target, char spare) {
  if (n == 0)
    return;
  if (n == 1) {
    cout << "Moving disk " << n << " from " << start << " to " << target
         << endl;
    return;
  }
  towers(n - 1, start, spare, target);
  cout << "Moving disk " << n << " from " << start << " to " << target << endl;
  towers(n - 1, spare, target, start);
}

int main() { towers(64, 'A', 'B', 'C'); }
