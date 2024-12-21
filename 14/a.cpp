#include <iostream>
#include <regex>
#include <string>
#include <utility>

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

int main() {
  regex robot_regex {"p=(-?\\d+),(-?\\d+) v=(-?\\d+),(-?\\d+)"};
  smatch robot_match;
  string line;
  
  long quadrants[4] {0, 0, 0, 0};

  while (getline(cin, line)) {
    regex_match(line, robot_match, robot_regex);
    robot bot = robot(
      stol(robot_match.str(1)),
      stol(robot_match.str(2)),
      stol(robot_match.str(3)),
      stol(robot_match.str(4))
    );

    bot.move(100);

    if (bot.pos.first < (N / 2) && bot.pos.second < (M / 2))
      ++quadrants[0];
    else if (bot.pos.first > (N / 2) && bot.pos.second < (M / 2))
      ++quadrants[1];
    else if (bot.pos.first > (N / 2) && bot.pos.second > (M / 2))
      ++quadrants[2];
    else if (bot.pos.first < (N / 2) && bot.pos.second > (M / 2))
      ++quadrants[3];
  }

  cout << quadrants[0] << " " << quadrants[1] << " " << quadrants[2] << " " << quadrants[3] << endl;

  long safety_factor {quadrants[0] * quadrants[1] * quadrants[2] * quadrants[3]};
  cout << safety_factor << endl;

  return 0;
}
