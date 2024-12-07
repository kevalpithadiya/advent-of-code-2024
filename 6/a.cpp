#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum orientation { UP=0, RIGHT=1, DOWN=2, LEFT=3 };
string orientation_chars = "^>v<";

vector<string> empty_path_map(size_t m, size_t n) {
  vector<string> path_map;
  
  for (size_t j = 0; j < m; j++) {
    path_map.push_back(string(n, '.'));
  }

  return path_map;
}

orientation right_turn(orientation dir) {
  return (orientation) (((size_t) dir + 1) % 4);
}

void print_map(vector<string> map) {
  for (const auto& line : map) {
    cout << line << '\n';
  }

  cout << endl;
}

int main() {
  // Parse the input into a subscriptable mapping
  vector<string> map;
  string line;
  while (getline(cin, line))
    map.push_back(line);

  // Size of map: m x n
  size_t m{map.size()}, n{map[0].length()};

  // Find the start location and orientation of the guard
  orientation dir;
  int y, x;

  for (size_t j = 0; j < m; j++) {
    for (size_t i = 0; i < n; i++) {
      size_t char_pos = orientation_chars.find(map[j][i]);

      if (char_pos != string::npos) {
        dir = (orientation) char_pos;
        y = j;
        x = i;
      }
    }
  }

  // Make the guard move around until he exits
  vector<string> path_map = empty_path_map(m, n);
  path_map[y][x] = 'X';

  while (true) {
    int next_x{x}, next_y{y};

    switch (dir) {
      case UP:
        next_y -= 1;
        break;
      case RIGHT:
        next_x += 1;
        break;
      case DOWN:
        next_y += 1;
        break;
      case LEFT:
        next_x -= 1;
    }

    // Check if the next location is outside the map
    if ((next_x == -1) || (next_x == n) || (next_y == -1) || (next_y == m)) {
      break;
    }

    // Check if the next location is an obstacle and perform a right turn if so
    while (map[next_y][next_x] == '#') {
      dir = right_turn(dir);

      next_x = x;
      next_y = y;

      switch (dir) {
        case UP:
          next_y -= 1;
          break;
        case RIGHT:
          next_x += 1;
          break;
        case DOWN:
          next_y += 1;
          break;
        case LEFT:
          next_x -= 1;
      }
    }

    // Update the guard location and orientation on the map
    map[y][x] = '.';
    x = next_x;
    y = next_y;
    map[y][x] = orientation_chars[dir];

    // Mark the new location as visited on the guard path
    path_map[y][x] = 'X';
  }

  // Count the number of locations on the guard path after he goes outside
  size_t acc{0};
  for (size_t j = 0; j < m; j++) {
    for (size_t i = 0; i < n; i++) {
      if (path_map[j][i] == 'X')
        acc++;
    }
  }

  cout << acc << endl;

  return 0;
}
