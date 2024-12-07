#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
  string line;
  unsigned long acc{0};

  while(getline(cin, line)) {
    regex mul_regex{"mul\\((\\d+),(\\d+)\\)"};
    sregex_iterator mul_begin = sregex_iterator(line.begin(), line.end(), mul_regex);
    sregex_iterator mul_end = sregex_iterator();

    for (sregex_iterator i = mul_begin; i != mul_end; ++i) {
      smatch match = *i;
      unsigned long a{stoul(match.str(1))}, b {stoul(match.str(2))};
      acc += a*b;
    }
  }

  cout << acc << endl;

  return 0;
}
