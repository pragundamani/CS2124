#include <iostream>
using namespace std;
void mystery(int n) {
  if (n > 1) {
    cout << 'a';
    mystery(n / 2);
    cout << 'b';
    mystery(n / 2);
  }

  cout << 'c';
}
int main() { mystery(4); }
