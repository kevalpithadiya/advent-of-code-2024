#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main() {
  regex a_regex {"Button A: X\\+(\\d+), Y\\+(\\d+)"};
  regex b_regex {"Button B: X\\+(\\d+), Y\\+(\\d+)"};
  regex p_regex {"Prize: X=(\\d+), Y=(\\d+)"};
  long total_cost{0};

  string line;
  while (getline(cin, line)) {
    smatch a_match;
    regex_match(line, a_match, a_regex);
    long ax {stol(a_match.str(1))}, ay {stol(a_match.str(2))};

    getline(cin, line);
    smatch b_match;
    regex_match(line, b_match, b_regex);
    long bx {stol(b_match.str(1))}, by {stol(b_match.str(2))};

    getline(cin, line);
    smatch p_match;
    regex_match(line, p_match, p_regex);
    long px {stol(p_match.str(1))}, py {stol(p_match.str(2))};

    getline(cin, line);

    // Check for min cost combination
    // 100 times pressing limit for both buttons

    long min_cost {0};
    // Loop through all possible no. of presses of b
    for (long b {0}; b <= 100; ++b) {
      // Calculate remaining x and y displacements required to reach the prize
      long rx {px - (b * bx)}, ry {py - (b * by)};
      
      // If any displacement is negative, not possible and further iterations will
      // be more negative, hence break out of loop
      if (rx < 0 || ry < 0)
        break;

      // Calculate required no. of presses of a to cover rx
      long a {rx / ax};

      // Skip if this value does not reach the prize
      if ((a * ax != rx) || (a * ay != ry))
        continue;

      // Viable combination of a and b, update min_cost
      long new_cost {3*a + b};
      if (min_cost == 0 || new_cost < min_cost)
        min_cost = new_cost;
    }

    total_cost += min_cost;
  }

  cout << total_cost << endl;

  return 0;
}
