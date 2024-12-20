#include <iostream>
#include <string>
#include <map>

using namespace std;
typedef map<unsigned long, size_t> freq_map;

void print_freq_map(freq_map stones) {
  for (auto [stone, freq] : stones) {
    cout << stone << ":" << freq << " ";
  }
  cout << endl;
}

void increment_count(freq_map& stones, unsigned long value, size_t freq) {
  if (stones.count(value))
    stones[value] += freq;
  else
    stones[value] = freq;
}

freq_map simulate_blink(const freq_map& stones) {
  freq_map new_stones;

  for (auto [stone, freq] : stones) {
    string stone_str{to_string(stone)};

    // Rule 1
    if (stone == 0)
      increment_count(new_stones, 1, freq);
    
    // Rule 2
    else if (stone_str.length() % 2 == 0) {
      size_t split_pos = stone_str.length() / 2;
      
      increment_count(new_stones, stoul(stone_str.substr(0, split_pos)), freq);
      increment_count(new_stones, stoul(stone_str.substr(split_pos, split_pos)), freq);
    }

    // Rule 3
    else
      increment_count(new_stones, stone * 2024, freq);
  }

  return new_stones;
};

int main() {
  // Parse input into a list of strings
  freq_map stones;
  unsigned long value;
  while(cin >> value)
    increment_count(stones, value, 1);
  
  print_freq_map(stones);

  const int BLINKS{75};

  for (size_t i{0}; i < BLINKS; i++) {
    stones = simulate_blink(stones);
  }

  // Count the cumulative frequence in the final map
  size_t acc{0};

  for (auto [_, freq] : stones)
    acc += freq;

  cout << acc << endl;

  return 0;
}
