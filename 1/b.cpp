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

  unsigned long n{id_list1.size()};

  // Sort both ID lists to obtain them in order
  sort(id_list1.begin(), id_list1.end());
  sort(id_list2.begin(), id_list2.end());

  // Accumulate the Similarity Score in one pass from the sorted ID lists
  unsigned long i{0}, j{0};
  unsigned long acc{0};

  while(i < (n-1) && j < (n-1)) {
    id1 = id_list1[i];
    id2 = id_list2[j];

    if (id1 < id2) {
      i++;
    }
    else if (id1 > id2) {
      j++;
    }
    else {
      acc += id1;
      j++;
    }
  }

  // Output the total distance
  cout << acc << endl;

  return 0;
}
