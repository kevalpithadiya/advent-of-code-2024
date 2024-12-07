#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

typedef vector<string> update;

int main() {
  unordered_map<string, bool> rules;
  vector<update> updates;
  string line;

  // Parse all rules
  while (getline(cin, line)) {
    if (line[0] == '\0')
      break;

    rules[line] = true;
  }

  // Parse all update page sequences
  while (getline(cin, line)) {
    update update;
    
    for (size_t i = 0; (3*i + 2) <= line.length(); i++) {
      update.push_back(line.substr(3*i, 2));
    }

    updates.push_back(update);
  }

  unsigned long acc{0};

  // Check all updates
  for (auto& update : updates) {
    bool incorrect = false;

    for (size_t i = 0; (i < update.size()); i++) {
      for (size_t j = i+1; (j < update.size()); j++) {
        // Create contradicitng rule key
        string key = update[j] + "|" + update[i];
        // Find the contradicting rule if it exists
        auto rule = rules.find(key);

        // If the contradicting rule exists
        if (rule != rules.cend()) {
          incorrect = true;

          // Swap the ith and jth entries
          iter_swap(update.begin() + i, update.begin() + j);
        }
      }
    }

    if (incorrect) {
      acc += stoul(update[update.size() / 2]);
    }
  }

  cout << acc << endl;

  return 0;
}
