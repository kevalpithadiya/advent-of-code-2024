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

  for (size_t y = 0; y < m; y++) {
    for (size_t x = 0; x < n; x++) {
      // If the current location is not an X, skip
      // Otherwise, check for a match in all directions
      if (puzzle[y][x] != 'X')
        continue;

      // +X
      if ((x+3 < n) && (puzzle[y][x+1] == 'M') && (puzzle[y][x+2] == 'A') && (puzzle[y][x+3] == 'S'))
        acc++;

      // -X
      if ((x >= 3) && (puzzle[y][x-1] == 'M')&& (puzzle[y][x-2] == 'A') && (puzzle[y][x-3] == 'S'))
        acc++;

      // +Y
      if ((y+3 < m) && (puzzle[y+1][x] == 'M') && (puzzle[y+2][x] == 'A') && (puzzle[y+3][x] == 'S'))
        acc++;

      // -Y
      if ((y >= 3) && (puzzle[y-1][x] == 'M')&& (puzzle[y-2][x] == 'A') && (puzzle[y-3][x] == 'S'))
        acc++;

      // +X+Y
      if ((x+3 < n) && (y+3 < m) && (puzzle[y+1][x+1] == 'M') && (puzzle[y+2][x+2] == 'A') && (puzzle[y+3][x+3] == 'S'))
        acc++;

      // -X-Y
      if ((x >= 3) && (y >= 3) && (puzzle[y-1][x-1] == 'M') && (puzzle[y-2][x-2] == 'A') && (puzzle[y-3][x-3] == 'S'))
        acc++;

      // +X-Y
      if ((x+3 < n) && (y >= 3) && (puzzle[y-1][x+1] == 'M') && (puzzle[y-2][x+2] == 'A') && (puzzle[y-3][x+3] == 'S'))
        acc++;

      // -X+Y
      if ((x >= 3) && (y+3 < m) && (puzzle[y+1][x-1] == 'M') && (puzzle[y+2][x-2] == 'A') && (puzzle[y+3][x-3] == 'S'))
        acc++;
    }
  }

  cout << acc << endl;

  return 0;
}
