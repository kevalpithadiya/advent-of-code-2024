#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

typedef pair<size_t, size_t> point;

void print_map(const vector<string>& plot_map) {
  for (auto const& row : plot_map)
    cout << row << endl;
}

void print_points(const vector<point>& points) {
  for (auto const [y, x] : points)
    cout << y << "," << x << " ";
  cout << endl;
}

vector<point> explore_region(vector<string>& plot_map, size_t y, size_t x, vector<vector<bool>>& visited, unsigned long& area) {
  const size_t m{plot_map.size()}, n{plot_map[0].length()};
  char cur_plot{plot_map[y][x]};
  
  visited[y][x] = true;
  plot_map[y][x] = '.';
  vector<point> points {point(y, x)};

  if ((y > 0) && (!visited[y-1][x]) && (plot_map[y-1][x] == cur_plot)) {
    auto new_points = explore_region(plot_map, y-1, x, visited, area);
    points.insert(points.end(), new_points.begin(), new_points.end());
    ++area;
  }

  if ((x > 0) && (!visited[y][x-1]) && (plot_map[y][x-1] == cur_plot)) {
    auto new_points = explore_region(plot_map, y, x-1, visited, area);
    points.insert(points.end(), new_points.begin(), new_points.end());
    ++area;
  }

  if ((y < m-1) && (!visited[y+1][x]) && (plot_map[y+1][x] == cur_plot)) {
    auto new_points = explore_region(plot_map, y+1, x, visited, area);
    points.insert(points.end(), new_points.begin(), new_points.end());
    ++area;
  }

  if ((x < n-1) && (!visited[y][x+1]) && (plot_map[y][x+1] == cur_plot)) {
    auto new_points = explore_region(plot_map, y, x+1, visited, area);
    points.insert(points.end(), new_points.begin(), new_points.end());
    ++area;
  }

  return points;
};

point find_unvisited(const vector<vector<bool>>& visited, size_t m, size_t n) {
  for (size_t y{0}; y < m; ++y) {
    for (size_t x{0}; x < n; ++x) {
      if (!visited[y][x])
        return point(y, x);
    }
  }

  return point(-1, -1);
}

// Yoinked from Sharath's (very clean) Implemententation
// https://github.com/sharaths21312/Advent-of-code-2024/blob/main/csharp%252Fd12.csx
unsigned long check_corner(const vector<string>& marked_plot_map, point p1, point p2, point p12) {
  auto [y1, x1] = p1;
  auto [y2, x2] = p2;
  auto [y12, x12] = p12;

  const size_t m{marked_plot_map.size()}, n{marked_plot_map[0].length()};
  unsigned long corners{0};

  bool c1 {(x1 >= 0 && x1 <= n-1 && y1 >= 0 && y1 <= m-1) && (marked_plot_map[y1][x1] == '.')};
  bool c2 {(x2 >= 0 && x2 <= n-1 && y2 >= 0 && y2 <= m-1) && (marked_plot_map[y2][x2] == '.')};
  bool c12 {(x12 >= 0 && x12 <= n-1 && y12 >= 0 && y12 <= m-1) && (marked_plot_map[y12][x12] == '.')};

  bool is_corner {(c1 && c2 && !c12) || (!c1 && !c2)};

  return is_corner ? 1 : 0;
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

    unsigned long area{1};
    vector<string> marked_plot_map = plot_map;
    vector<point> points = explore_region(marked_plot_map, y, x, visited, area);

    unsigned long corners{0};
    for (auto const [y, x] : points) {
      corners += check_corner(marked_plot_map, point(y-1, x), point(y, x-1), point(y-1, x-1));
      corners += check_corner(marked_plot_map, point(y-1, x), point(y, x+1), point(y-1, x+1));
      corners += check_corner(marked_plot_map, point(y+1, x), point(y, x-1), point(y+1, x-1));
      corners += check_corner(marked_plot_map, point(y+1, x), point(y, x+1), point(y+1, x+1));
    }

    acc += area * corners;
  }
  
  cout << acc << endl;

  return 0;
}
