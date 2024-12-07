#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum orientation { UP=0, RIGHT=1, DOWN=2, LEFT=3 };
string orientation_chars = "^>v<";

typedef tuple<int, int, orientation> state;

orientation right_turn(orientation dir) {
  return (orientation) (((size_t) dir + 1) % 4);
}

tuple<int, int> next_pos(int y, int x, orientation dir) {
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

  return tuple(next_y, next_x);
}

void print_map(vector<string> map) {
  for (const auto& line : map) {
    cout << line << '\n';
  }

  cout << endl;
}

state get_start_state(vector<string> map) {
  orientation dir;
  int x, y;

  size_t m{map.size()}, n{map[0].length()};

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

  return state(y, x, dir);
}

vector<state> sim_original(vector<string> map, state start_state) {
  size_t m{map.size()}, n{map[0].length()};
  auto[y, x, dir] = start_state;

  vector<state> visited_states;
  visited_states.push_back(state(y, x, dir));

  while (true) {
    auto[next_y, next_x] = next_pos(y, x, dir);

    // Check if the next location is outside the map
    if ((next_x == -1) || (next_x == n) || (next_y == -1) || (next_y == m)) {
      break;
    }

    // Check if the next location is an obstacle and perform a right turn if so
    if (map[next_y][next_x] == '#') {
      dir = right_turn(dir);
      map[y][x] = orientation_chars[dir];
    }
    // Otherwise simply move forward
    else {
      map[y][x] = '.';
      map[next_y][next_x] = orientation_chars[dir];
      x = next_x;
      y = next_y;
    }

    visited_states.push_back(state(y, x, dir));
  }

  return visited_states;
}

bool sim_loop_check(vector<string> map, state start_state, int oy, int ox) {
  vector<state> visited_states;
  visited_states.push_back(start_state);

  // Add new obstruction
  map[oy][ox] = '#';

  // Start the simulation
  size_t m{map.size()}, n{map[0].length()};
  auto[y, x, dir] = start_state;

  while (true) {
    auto[next_y, next_x] = next_pos(y, x, dir);

    // Check if the next location is outside the map
    if ((next_x == -1) || (next_x == n) || (next_y == -1) || (next_y == m)) {
      break;
    }

    // Check if the next location is an obstacle and perform a right turn if so
    if (map[next_y][next_x] == '#') {
      dir = right_turn(dir);
      map[y][x] = orientation_chars[dir];
    }
    // Otherwise simply move forward
    else {
      map[y][x] = '.';
      map[next_y][next_x] = orientation_chars[dir];
      x = next_x;
      y = next_y;
    }

    // Check if state was previously encountered
    state new_state = state(y, x, dir);

    if (find(visited_states.begin(), visited_states.end(), new_state) != visited_states.end()) {
      // cout << y << ' ' << x << ' ' << orientation_chars[dir] << " | ";
      // cout << oy << ' ' << ox << endl;
      return true;
    }

    visited_states.push_back(state(y, x, dir));
  }

  return false;
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
  state start_state = get_start_state(map);

  // Obtain the original path / visited states
  vector<state> visited_states = sim_original(map, start_state);

  // Check for loop causing obstruction positions
  size_t acc{0};

  // A suitable location for the new obstruction can only be at some
  // next location for any of the visited states. If an obstruction
  // exists at the next location, we simply skip it from considering.

  for (size_t k = 0; k < visited_states.size(); k++) {
    state lstart = visited_states[k];
    auto [lstart_y, lstart_x, lstart_dir] = lstart;

    // Potential Obstruction position is the position next from current state
    auto[pot_oy, pot_ox] = next_pos(lstart_y, lstart_x, lstart_dir);
    
    // Skip if the potential position is outside the map or if an obstruction already exists there
    if ((pot_ox == -1) || (pot_ox == n) || (pot_oy == -1) || (pot_oy == m) || map[pot_oy][pot_ox] == '#') {
      continue;
    }

    // Skip if guard was previously on the potential position
    bool visited = false;
    for (int l = 0; l <= k; l++) {
      const auto[vy, vx, vdir] = visited_states[l];
      if (pot_oy == vy && pot_ox == vx)
        visited |= true;
    }
    if (visited)
      continue;

    // We have established that an obstruction can be safely put on the
    // new position. To check now if it forms a loop
    // cerr << k << '/' << visited_states.size() << '\r';
    if (sim_loop_check(map, start_state, pot_oy, pot_ox)) {
      acc++;
    }
  }

  cout << acc << endl;

  return 0;
}
