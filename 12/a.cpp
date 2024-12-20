#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

typedef tuple<size_t, size_t> location;

void print_map(const vector<string>& plot_map) {
  for (auto const& row : plot_map)
    cout << row << endl;
}

void explore_region(vector<string>& plot_map, size_t y, size_t x, vector<vector<bool>>& visited, unsigned long& area, unsigned long& perimeter) {
  const size_t m{plot_map.size()}, n{plot_map[0].length()};
  char cur_plot{plot_map[y][x]};
  
  visited[y][x] = true;

  if ((y > 0) && (!visited[y-1][x]) && (plot_map[y-1][x] == cur_plot)) {
    explore_region(plot_map, y-1, x, visited, area, perimeter);
    ++area;
  }
  else if ((y == 0) || (plot_map[y-1][x] != cur_plot))
    perimeter += 1;

  if ((x > 0) && (!visited[y][x-1]) && (plot_map[y][x-1] == cur_plot)) {
    explore_region(plot_map, y, x-1, visited, area, perimeter);
    ++area;
  }
  else if ((x == 0) || (plot_map[y][x-1] != cur_plot))
    perimeter += 1;

  if ((y < m-1) && (!visited[y+1][x]) && (plot_map[y+1][x] == cur_plot)) {
    explore_region(plot_map, y+1, x, visited, area, perimeter);
    ++area;
  }
  else if ((y == m-1) || (plot_map[y+1][x] != cur_plot))
    perimeter += 1;

  if ((x < n-1) && (!visited[y][x+1]) && (plot_map[y][x+1] == cur_plot)) {
    explore_region(plot_map, y, x+1, visited, area, perimeter);
    ++area;
  }
  else if ((x == n-1) || (plot_map[y][x+1] != cur_plot))
    perimeter += 1;
};

tuple<size_t, size_t> find_unvisited(const vector<vector<bool>>& visited, size_t m, size_t n) {
  for (size_t y{0}; y < m; ++y) {
    for (size_t x{0}; x < n; ++x) {
      if (!visited[y][x])
        return tuple(y, x);
    }
  }

  return tuple(-1, -1);
}

int main() {
  vector<string> plot_map;
  string line;
  while (getline(cin, line))
    plot_map.push_back(line);

  // Map to keep track of visited nodes
  const size_t m{plot_map.size()}, n{plot_map[0].length()};
  vector<vector<bool>> visited {vector<vector<bool>>(m, vector<bool>(n, false))};

  unsigned long acc{0};
  while (true) {
    auto [y, x] = find_unvisited(visited, m, n);

    if (y == -1)
      break;

    unsigned long area{1}, perimeter{0};
    explore_region(plot_map, y, x, visited, area, perimeter);

    // cout << y << "," << x << " | " << area << " * " << perimeter << endl;
    // print_map(plot_map);

    acc += area * perimeter;
  }
  
  cout << acc << endl;

  return 0;
}
