#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  // Intialize vectors to store input ID lists
  vector<int> id_list1, id_list2;

  // Read and store IDs one-by-one
  int id1, id2;
  while (cin >> id1 >> id2) {
    id_list1.push_back(id1);
    id_list2.push_back(id2);
  }

  // Sort both ID lists to obtain them in order
  sort(id_list1.begin(), id_list1.end());
  sort(id_list2.begin(), id_list2.end());

  // Accumulate the distances
  int acc{0};
  for (int i = 0; i < id_list1.size(); i++) {
    acc += abs(id_list2[i] - id_list1[i]);
  }

  // Output the total distance
  cout << acc << endl;

  return 0;
}
