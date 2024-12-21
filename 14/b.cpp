#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Width and Height
const long N {101}, M {103};

class robot {
public:
  pair<long, long> pos;
  pair<long, long> vel;

  robot (long pos_x, long pos_y, long vel_x, long vel_y) {
    pos = pair<long, long>(pos_x, pos_y);
    vel = pair<long, long>(vel_x, vel_y);
  }

  // Move the robot for given no. of seconds
  void move(long seconds = 1) {
    pos.first = (pos.first + vel.first * seconds) % N;
    pos.second = (pos.second + vel.second * seconds) % M;

    // Correct for negative remainder
    if (pos.first < 0)
      pos.first += N;
    if (pos.second < 0)
      pos.second += M;
  }
};

vector<string> gen_bot_grid(const vector<robot>& robots) {
  vector<string> bot_grid {vector<string>(M, string(N, '.'))};

  for (const auto& bot : robots)
    bot_grid[bot.pos.second][bot.pos.first] = 'o';

  return bot_grid;
};

void print_bot_grid(const vector<string>& bot_grid) {
  for (const auto& row : bot_grid)
    cout << row << "\n";
  cout << endl;
}

size_t explore_conn_comp(vector<string>& bot_grid, size_t x, size_t y) {
  size_t size{1};
  bot_grid[y][x] = '#';

  if ((y > 0) && (bot_grid[y-1][x] == 'o'))
    size += explore_conn_comp(bot_grid, x, y-1);
  if ((x > 0) && (bot_grid[y][x-1] == 'o'))
    size += explore_conn_comp(bot_grid, x-1, y);
  if ((y < M-1) && (bot_grid[y+1][x] == 'o'))
    size += explore_conn_comp(bot_grid, x, y+1);
  if ((x < N-1) && (bot_grid[y][x+1] == 'o'))
    size += explore_conn_comp(bot_grid, x+1, y);

  return size;
}

size_t largest_conn_comp(vector<string>& bot_grid) {
  size_t max_size{0};
  size_t cur_size{0};

  for (size_t y{0}; y < M; ++y) {
    for (size_t x{0}; x < N; ++x) {
      if ( (bot_grid[y][x] == 'o') && (cur_size = explore_conn_comp(bot_grid, x, y)) > max_size)
        max_size = cur_size;
    }
  }

  return max_size;
}

int main() {
  regex robot_regex {"p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)"};
  smatch robot_match;
  string line;
  
  vector<robot> robots;

  while (getline(cin, line)) {
    regex_match(line, robot_match, robot_regex);
    robots.push_back(robot(
      stol(robot_match.str(1)),
      stol(robot_match.str(2)),
      stol(robot_match.str(3)),
      stol(robot_match.str(4))
    ));
  }

  const double threshold = 0.1 * robots.size();

  for (size_t i {1}; i <= 10000; ++i) {
    // Move the bot for 1 second
    for_each(robots.begin(), robots.end(), [](robot& bot) { bot.move(); });

    // Produce bot grid
    auto bot_grid {gen_bot_grid(robots)};

    // Check if the largest connected component is large
    size_t comp_size {largest_conn_comp(bot_grid)};
    cout << comp_size << "\r";
    if (comp_size > threshold) {
      cout << i << "\t" << comp_size << endl;
      print_bot_grid(bot_grid);
    }   
  };

  return 0;
}
