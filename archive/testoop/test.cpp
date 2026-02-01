#include <iostream>
#include <vector>

using namespace std;

int main() {
  cout << "Welcome to CS-UY 2124!" << endl;
  int x = 5;
  cout << "The value of x is " << x << endl;

  vector<int> nums{1, 2, 3};
  for (int i : nums) {
    cout << i << " ";
  }
  return 0;
}
