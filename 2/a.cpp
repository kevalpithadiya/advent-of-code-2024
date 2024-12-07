#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool check_safe(vector<long>& report) {
  long prev{report[0]}, cur{report[1]};
  long prev_diff, cur_diff;
  bool safe = true;

  prev_diff = cur - prev;
  prev = cur;

  if (abs(prev_diff) < 1 || abs(prev_diff) > 3) {
    safe = false;
  }

  for (unsigned long i = 2; i < report.size(); i++) {
    cur = report[i];
    cur_diff = cur - prev;

    if ((cur_diff > 0 && prev_diff < 0) || (cur_diff < 0 && prev_diff > 0) || (abs(cur_diff) < 1) || (abs(cur_diff) > 3)) {
      safe = false;
      break;
    }

    prev = cur;
    prev_diff = cur_diff;
  }

  return safe;
}

int main() {
  // Stores current report line
  string line;
  
  // Accumulator for safe reports
  unsigned long acc{0};

  // Loop through all lines
  while (getline(cin, line)) {
    istringstream line_stream{line};
    vector<long> report;
    
    long level;
    while (line_stream >> level)
      report.push_back(level);

    if (check_safe(report)) {
      acc++;
    }
  }

  cout << acc << endl;

  return 0;
}
