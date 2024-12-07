#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void print_vec(vector<unsigned long> terms) {
  for (const auto& term : terms)
    cout << term << ' ';

  cout << endl;
}

// Recursively check if adding / multiplying / concatenating the first two term gives the desired result
bool is_valid(const unsigned long result, const vector<unsigned long> terms) {

  // Base Case
  if (terms.size() == 1) {
    if (terms[0] == result)
      return true;
    else
      return false;
  }

  // Adding first two terms
  vector<unsigned long> add_terms = terms;
  add_terms[1] = add_terms[0] + add_terms[1];
  add_terms.erase(add_terms.begin());
  bool add = is_valid(result, add_terms);

  // Multiplying first two terms
  vector<unsigned long> mul_terms = terms;
  mul_terms[1] = mul_terms[0] * mul_terms[1];
  mul_terms.erase(mul_terms.begin());
  bool mul = is_valid(result, mul_terms);

  // Concatenating first two terms
  vector<unsigned long> con_terms = terms;
  con_terms[1] = stoul(to_string(con_terms[0]) + to_string(con_terms[1]));
  con_terms.erase(con_terms.begin());
  bool con = is_valid(result, con_terms);

  return (add | mul | con);
};

int main() {
  unsigned long acc{0};

  // Read an test equations one by one
  string line;
  while (getline(cin, line)) {
    unsigned long result;
    vector<unsigned long> terms;

    // Parse result value
    long col_pos{distance(line.begin(), find(line.begin(), line.end(), ':'))};
    result = stoul(line.substr(0, col_pos));
    
    // Parse terms
    istringstream line_stream{line.substr(col_pos + 2)};
    unsigned long term;
    while (line_stream >> term)
      terms.push_back(term);

    // Check if any operator combination works
    if (is_valid(result, terms))
      acc += result;
  }

  cout << acc << endl;

  return 0;
}
