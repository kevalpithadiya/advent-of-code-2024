#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  // Parse input
  vector<int> files;
  vector<int> frees;
  
  string line;
  getline(cin, line);

  files.push_back(line[0] - 0x30);
  for (size_t i = 1; i < line.length(); i += 2) {
    frees.push_back(line[i] - 0x30);
    files.push_back(line[i+1] - 0x30);
  }

  // File index serves as file ID
  size_t block{0}, free_idx{0}, left_file_idx{0}, right_file_idx{files.size() - 1};
  size_t acc{0};
  bool free_block{false};

  while ((files[left_file_idx] != 0) || (files[right_file_idx] != 0)) {
    if (free_block) {
      if (frees[free_idx] == 0) {
        free_block = false;
        continue;
      }
      
      acc += (right_file_idx * block);
      --files[right_file_idx];
      --frees[free_idx];

      if (files[right_file_idx] == 0) {
        --right_file_idx;
      }

      ++block;
    }

    else {
      acc += (left_file_idx * block);
      --files[left_file_idx];

      // If file ends
      if (files[left_file_idx] == 0) {
        free_block = true;
        free_idx = left_file_idx;
        ++left_file_idx;
      }

      ++block;
    }
  }

  cout << acc << endl;

  return 0;
}
