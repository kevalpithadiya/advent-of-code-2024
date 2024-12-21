#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
typedef pair<long, long> yx;

void print_map(const vector<string>& map) {
  for (const auto& row : map)
    cout << row << "\n";
  cout << endl;
}

yx get_bot_pos(const vector<string>& map) {
  const size_t M {map.size()}, N{map[0].length()};

  for (size_t y{0}; y < M; ++y) {
    for (size_t x{0}; x < N; ++x) {
      if (map[y][x] == '@')
        return yx(y, x);
    }
  }

  return yx(-1, -1);
}

void sim_move(vector<string>& map, yx& bot_pos, char move) {
  // Determine move direction vector
  yx dir;
  switch(move) {
    case '^':
      dir = yx(-1, 0);
      break;
    case 'v':
      dir = yx(1, 0);
      break;
    case '>':
      dir = yx(0, 1);
      break;
    case '<':
      dir = yx(0, -1);
      break;
    // Skip move if any other character
    default:
      return;
  }

  const size_t M {map.size()}, N{map[0].length()};

  // Search for first empty position in the move direction
  yx s_pos = {bot_pos};
  while (s_pos.first > 0 && s_pos.first < M-1 && s_pos.second > 0 && s_pos.second < N-1) {
    s_pos = yx(s_pos.first + dir.first, s_pos.second + dir.second);

    // If no empty position found, skip move
    if (map[s_pos.first][s_pos.second] == '#')
      return;

    // Empty position found, break out of loop
    if (map[s_pos.first][s_pos.second] == '.')
      break;
  }

  // Shift boxes or bot along the direction if empty position found
  while (s_pos != bot_pos) {
    yx p_pos {yx(s_pos.first - dir.first, s_pos.second - dir.second)};
    map[s_pos.first][s_pos.second] = map[p_pos.first][p_pos.second];
    s_pos = p_pos;
  }

  // Update the bot position and mark empty the original bot position
  map[bot_pos.first][bot_pos.second] = '.';
  bot_pos = yx(bot_pos.first + dir.first, bot_pos.second + dir.second);
}

int main() {
  vector<string> map;
  string line;

  // Parse Map
  while (getline(cin, line)) {
    if (line[0] == '\0')
      break;
    map.push_back(line);
  }

  // print_map(map);

  // Search for initial position of the bot
  yx bot_pos = get_bot_pos(map);

  // Go through all moves
  char move{};
  while (!cin.eof()) {
    move = cin.get();

    sim_move(map, bot_pos, move);

    // print_map(map);
  }

  // Compute cumulative GPS coordinates
  size_t acc{0};
  const size_t M {map.size()}, N{map[0].length()};

  for (size_t y{0}; y < M; ++y) {
    for (size_t x{0}; x < N; ++x) {
      if (map[y][x] == 'O')
        acc += (100*y) + x;
    }
  }

  cout << acc << endl;

  return 0;
}
