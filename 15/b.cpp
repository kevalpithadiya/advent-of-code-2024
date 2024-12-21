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

// tile_pos is always of the '[' character
bool try_tile_move(vector<string>& map, yx tile_pos, char move) {
  auto [y, x] {tile_pos};

  switch(move) {
  
  case '>': {
    if (map[y][x+2] == '.')
      return true;
    else if (map[y][x+2] == '[')
      return try_tile_move(map, yx(y, x+2), move);
    break;
  }

  case '<': {
    if (map[y][x-1] == '.')
      return true;
    else if (map[y][x-2] == '[')
      return try_tile_move(map, yx(y, x-2), move);
    break;
  }

  case '^': {
    bool left_move{false}, right_move{false};

    if (map[y-1][x] == '.')
      left_move = true;
    // Aligned box case
    else if (map[y-1][x] == '[')
      left_move = right_move = try_tile_move(map, yx(y-1, x), move);
    else if (map[y-1][x] == ']')
      left_move = try_tile_move(map, yx(y-1, x-1), move);

    // Only for aligned box case
    if (right_move)
      return true;

    if (map[y-1][x+1] == '.')
      right_move = true;
    else if (map[y-1][x+1] == '[')
      right_move = try_tile_move(map, yx(y-1, x+1), move);

    return (left_move && right_move);
  }

  case 'v': {
    bool left_move{false}, right_move{false};

    if (map[y+1][x] == '.')
      left_move = true;
    // Aligned box case
    else if (map[y+1][x] == '[')
      left_move = right_move = try_tile_move(map, yx(y+1, x), move);
    else if (map[y+1][x] == ']')
      left_move = try_tile_move(map, yx(y+1, x-1), move);

    // Only for aligned box case
    if (right_move)
      return true;

    if (map[y+1][x+1] == '.')
      right_move = true;
    else if (map[y+1][x+1] == '[')
      right_move = try_tile_move(map, yx(y+1, x+1), move);

    return (left_move && right_move);
  }
  }

  return false;
}

void do_tile_move(vector<string>& map, yx tile_pos, char move) {
  auto [y, x] {tile_pos};

  switch(move) {
  
  case '>': {
    if (map[y][x+2] == '[')
      do_tile_move(map, yx(y, x+2), move);

    map[y][x] = '.';
    map[y][x+1] = '[';
    map[y][x+2] = ']';
    break;
  }

  case '<': {
    if (map[y][x-2] == '[')
      do_tile_move(map, yx(y, x-2), move);

    map[y][x-1] = '[';
    map[y][x] = ']';
    map[y][x+1] = '.'; 
    break;
  }

  case '^': {
    if (map[y-1][x] == '[')
      do_tile_move(map, yx(y-1, x), move);
    else {
      if (map[y-1][x] == ']')
        do_tile_move(map, yx(y-1, x-1), move);
      if (map[y-1][x+1] == '[')
        do_tile_move(map, yx(y-1, x+1), move);
    }

    map[y][x] = map[y][x+1] = '.';
    map[y-1][x] = '[';
    map[y-1][x+1] = ']';
    break;
  }

  case 'v': {
    if (map[y+1][x] == '[')
      do_tile_move(map, yx(y+1, x), move);
    else {
      if (map[y+1][x] == ']')
        do_tile_move(map, yx(y+1, x-1), move);
      if (map[y+1][x+1] == '[')
        do_tile_move(map, yx(y+1, x+1), move);
    }

    map[y][x] = map[y][x+1] = '.';
    map[y+1][x] = '[';
    map[y+1][x+1] = ']';
    break;
  }
  }
}

void sim_move(vector<string>& map, yx bot_pos, char move) {
  auto [y, x] = bot_pos;

  switch (move) {
  
  case '>': {
    if (map[y][x+1] == '.') {
      map[y][x] = '.';
      map[y][x+1] = '@';
      return;
    }

    if ((map[y][x+1] == '[') && (try_tile_move(map, yx(y, x+1), move))) {
      do_tile_move(map, yx(y, x+1), move);
      map[y][x] = '.';
      map[y][x+1] = '@';
      return;
    }

    break;
  }

  case '<': {
    if (map[y][x-1] == '.') {
      map[y][x] = '.';
      map[y][x-1] = '@';
      return;
    }

    if ((map[y][x-2] == '[') && (try_tile_move(map, yx(y, x-2), move))) {
      do_tile_move(map, yx(y, x-2), move);
      map[y][x] = '.';
      map[y][x-1] = '@';
    }

    break;
  }

  case '^': {
    if (map[y-1][x] == '.') {
      map[y][x] = '.';
      map[y-1][x] = '@';
      return;
    }

    if ((map[y-1][x] == '[') && try_tile_move(map, yx(y-1, x), move)) {
      do_tile_move(map, yx(y-1, x), move);
      map[y][x] = '.';
      map[y-1][x] = '@';
      return;
    }

    if ((map[y-1][x] == ']') && try_tile_move(map, yx(y-1, x-1), move)) {
      do_tile_move(map, yx(y-1, x-1), move);
      map[y][x] = '.';
      map[y-1][x] = '@';
      return;
    }

    break;
  }

  case 'v': {
    if (map[y+1][x] == '.') {
      map[y][x] = '.';
      map[y+1][x] = '@';
      return;
    }

    if ((map[y+1][x] == '[') && try_tile_move(map, yx(y+1, x), move)) {
      do_tile_move(map, yx(y+1, x), move);
      map[y][x] = '.';
      map[y+1][x] = '@';
      return;
    }

    if ((map[y+1][x] == ']') && try_tile_move(map, yx(y+1, x-1), move)) {
      do_tile_move(map, yx(y+1, x-1), move);
      map[y][x] = '.';
      map[y+1][x] = '@';
      return;
    }

    break;
  }

  }
}

int main() {
  vector<string> map;
  string line;

  // Parse Map
  while (getline(cin, line)) {
    if (line[0] == '\0')
      break;
    
    // Construct the wider lines
    string wide_line{""};
    for (const auto& tile : line) {
      switch(tile) {
      case '#':
        wide_line += "##";
        break;
      case '.':
        wide_line += "..";
        break;
      case 'O':
        wide_line += "[]";
        break;
      case '@':
        wide_line += "@.";
        break;
      }
    }

    map.push_back(wide_line);
  }

  // print_map(map);

  // Search for initial position of the bot

  // Go through all moves
  char move{};
  while (!cin.eof()) {
    move = cin.get();
    
    if (move == '\n')
      continue;

    yx bot_pos = get_bot_pos(map);
    sim_move(map, bot_pos, move);

    // cout << move << endl;
    // print_map(map);
  }

  // Compute cumulative GPS coordinates
  size_t acc{0};
  const size_t M {map.size()}, N{map[0].length()};

  for (size_t y{0}; y < M; ++y) {
    for (size_t x{0}; x < N; ++x) {
      if (map[y][x] == '[')
        acc += (100*y) + x;
    }
  }

  cout << acc << endl;

  return 0;
}
