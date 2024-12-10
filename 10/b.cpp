#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t get_trail_rating(vector<string>& map, size_t j, size_t i) {
  size_t score{0};
  char height{map[j][i]};

  const size_t m{map.size()}, n{map[0].length()};

  // Base Case - Max Height Reached
  if (height == '9') {
    return 1;
  }

  // Recursively search for next step
  if ((j > 0) && (map[j-1][i] == height + 1))  // Up
    score += get_trail_rating(map, j-1, i);
  
  if ((j < m-1) && (map[j+1][i] == height + 1))  // Down
    score += get_trail_rating(map, j+1, i);
  
  if ((i > 0) && (map[j][i-1] == height + 1))  // Left
    score += get_trail_rating(map, j, i-1);
  
  if ((i < n-1) && (map[j][i+1] == height + 1)) // Right
    score += get_trail_rating(map, j, i+1);

  return score;
}

int main() {
  // Parse Input
  vector<string> map;
  string line;
  while(getline(cin, line))
    map.push_back(line);

  const size_t m{map.size()}, n{map[0].length()};

  // Find all trailheads and initiate search for trails, accumulate scores
  size_t acc{0};

  for (size_t j = 0; j < m; j++) {
    for (size_t i = 0; i < n; i++) {
      if (map[j][i] == '0') {
        size_t score = get_trail_rating(map, j, i);
        acc += score;
      }
    }
  }

  cout << acc << endl;

  return 0;
}
