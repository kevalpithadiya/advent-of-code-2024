#include <cstdlib>
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

bool check_safe_tol(vector<long>& report) {
  for (unsigned long i = 0; i < report.size(); i++) {
    // Make a copy of the report
    vector<long> tol_report{report};

    // Remove i'th level from the report
    tol_report.erase(tol_report.begin() + i);

    if (check_safe(tol_report))
      return true;
  }

  return false;
}

int main() {
  // Stores current report line
  string line;
  
  // Accumulator for safe reports
  unsigned long acc{0};

  // Loop through all lines
  while (getline(cin, line)) {
    // Parse report into a vector of integer levels
    istringstream line_stream{line};
    vector<long> report;
    
    long level;
    while (line_stream >> level)
      report.push_back(level);

    if (check_safe_tol(report))
      acc++;
  }

  cout << acc << endl;

  return 0;
}
