#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <map>
#include <tuple>

using namespace std;
typedef tuple<int, int> location;

map<char, vector<location>> get_antenna_map(const vector<string> input_map) {
  map<char, vector<location>> antenna_map;
  const size_t m{input_map.size()}, n{input_map[0].length()};

  for (size_t j = 0; j < m; ++j) {
    for (size_t i = 0; i < n; ++i) {
      char antenna_type = input_map[j][i];

      if (antenna_type != '.') {
        if (antenna_map.find(antenna_type) == antenna_map.end())
          antenna_map[antenna_type] = vector<location> {location(j, i)};
        else {
          antenna_map[antenna_type].push_back(location(j, i));
        }
      }
    }
  }

  return antenna_map;
}

void mark_antinodes(const location l1, const location l2, vector<vector<bool>>& antinodes) {
  auto[y1, x1] {l1};
  auto[y2, x2] {l2};

  const size_t m{(antinodes.size())}, n{(antinodes[0].size())};

  // Since two antennas are in line, their locations will have antinodes
  antinodes[y1][x1] = true;
  antinodes[y2][x2] = true;

  // Mark all other locations on the line joining them as antinodes
  int dely{y2 - y1}, delx{x2-x1};
  int divisor = gcd(dely, delx);
  dely /= divisor;
  delx /= divisor;

  // Scan through all integral locations on the line
  int x{x1 - delx}, y{y1 - dely};
  while (x >= 0 && x < n && y >= 0 && y < m) {
    antinodes[y][x] = true;
    x -= delx;
    y -= dely;
  }

  x = x1 + delx;
  y = y1 + dely;
  while (x >= 0 && x < n && y >= 0 && y < m) {
    antinodes[y][x] = true;
    x += delx;
    y += dely;
  }
}

int main() {
  // Read input map
  vector<string> input_map;
  string line;
  while (getline(cin, line))
    input_map.push_back(line);

  const size_t m{input_map.size()}, n{input_map[0].length()};

  // Create a mapping of antenna types to all corresponding antenna locations
  map<char, vector<location>> antenna_map = get_antenna_map(input_map);

  // Create a 2D bool map to mark positions of antinodes
  vector<vector<bool>> antinodes;
  for (size_t j = 0; j < m; ++j) {
    antinodes.push_back(vector<bool> {});
    for (size_t i = 0; i < n; ++i) {
      antinodes[j].push_back(false);
    }
  }

  // Loop through all different antenna types and mark all the possible antinode positions
  for (auto antenna : antenna_map) {
    auto[antenna_type, locations] {antenna};

    for (size_t i = 0; i < locations.size(); ++i) {
      for (size_t j = i+1; j < locations.size(); ++j) {
        mark_antinodes(locations[i], locations[j], antinodes);
      }
    }
  }

  // Loop through the bool map to count number of antinodes
  size_t acc{0};
  for (size_t j = 0; j < m; ++j) {
    for (size_t i = 0; i < n; ++i) {
      if (antinodes[j][i])
        ++acc;
    }
  }

  cout << acc << endl;

  return 0;
}
