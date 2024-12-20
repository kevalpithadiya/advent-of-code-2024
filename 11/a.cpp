#include <iostream>
#include <list>
#include <string>

using namespace std;

void print_stones(const list<string>& stones) {
  for (const string stone : stones) 
    cout << stone << " ";
  cout << endl;
}

list<string> simulate_blink(const list<string>& stones) {
  list<string> new_stones;

  for (auto const& stone : stones) {
    // Rule 1: Value 0
    if (stone == "0")
      new_stones.push_back("1");

    // Rule 2: Even number of digits
    else if (stone.length() % 2 == 0) {
      size_t split_pos = stone.length() / 2;
      
      // Separate into two stones
      string stone1{stone.substr(0, split_pos)};
      string stone2{stone.substr(split_pos, split_pos)};

      // Prune leading zeros (only possible in stone2)
      stone2 = to_string(stoul(stone2));

      new_stones.push_back(stone1);
      new_stones.push_back(stone2);
    }

    // Rule 3: Multiply by 2024
    else {
      new_stones.push_back(to_string(stoul(stone) * 2024));
    }
  }

  return new_stones;
}

int main() {
  // Parse input into a list of strings
  list<string> stones;
  string value;
  while(cin >> value)
    stones.push_back(value);
  
  // print_stones(stones);

  // Perform blink simulation
  const int BLINKS {25};

  for (size_t i{0}; i < BLINKS; ++i) {
    // cout << "Simulation " << i << endl;
    stones = simulate_blink(stones);
    // print_stones(stones);
  }

  cout << stones.size() << endl;

  return 0;
}
