#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> puzzle;
  string line;
  while (getline(cin, line))
    puzzle.push_back(line);

  size_t n{puzzle[0].length()}, m{puzzle.size()};
  unsigned long acc{0};

  for (size_t y = 1; y < m-1; y++) {
    for (size_t x = 1; x < n-1; x++) {
      // If the current location is not an 'A', skip
      // Otherwise check for all possible X-MASes
      if (puzzle[y][x] != 'A')
        continue;

      bool diag1{false}, diag2{false};

      // \ Diagonal
      diag1 |= (puzzle[y-1][x-1] == 'M' && puzzle[y+1][x+1] == 'S');
      diag1 |= (puzzle[y-1][x-1] == 'S' && puzzle[y+1][x+1] == 'M');

      // / Diagonal
      diag2 |= (puzzle[y-1][x+1] == 'M' && puzzle[y+1][x-1] == 'S');
      diag2 |= (puzzle[y-1][x+1] == 'S' && puzzle[y+1][x-1] == 'M');

      if (diag1 && diag2)
        acc++;
    }
  }

  cout << acc << endl;

  return 0;
}
