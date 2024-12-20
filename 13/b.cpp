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
    long px {10000000000000 + stol(p_match.str(1))}, py {10000000000000 + stol(p_match.str(2))};
    getline(cin, line);

    // To solve system of linear equations in a & b
    // (1) ax.a + bx.b = px
    // (2) ay.a + by.b = py

    long delta {ax*by - ay*bx};
    
    // Inconsistent Equations
    if (delta == 0) {
      cout << "Inconsistent" << endl;
    }
    // Consistent Equations
    // Only one possible solution
    else {
      long delta_a {px*by - py*bx};
      long delta_b {ax*py - ay*px};

      long a = delta_a / delta;
      long b = delta_b / delta;

      if ((ax*a + bx*b == px) && (ay*a + by*b == py))
        total_cost += (3*a + b);
    }
  }

  cout << total_cost << endl;

  return 0;
}
