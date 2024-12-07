#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
  string line;
  unsigned long acc{0};
  bool enabled = true;

  while(getline(cin, line)) {
    // Capture Groups - 1: do(), 2: don't(), 3: mul, 4: a, 5: b
    regex token_regex{"(do\\(\\))|(don't\\(\\))|(?:(mul)\\((\\d+),(\\d+)\\))"};
    sregex_iterator token_begin = sregex_iterator(line.begin(), line.end(), token_regex);
    sregex_iterator token_end = sregex_iterator();

    for (sregex_iterator i = token_begin; i != token_end; ++i) {
      smatch match = *i;

      if (match[1].length()) {
        enabled = true;
      }
      else if (match[2].length()) {
        enabled = false;
      }

      if (enabled && match[3].length()) {
        unsigned long a{stoul(match.str(4))}, b{stoul(match.str(5))};
        acc += a*b;
      }
    }
  }

  cout << acc << endl;

  return 0;
}
