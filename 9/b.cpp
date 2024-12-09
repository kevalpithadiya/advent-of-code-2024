#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// file<pos, id, size>
typedef tuple<size_t, size_t, int> file_t;
// 
typedef tuple<size_t, int> free_t;

void print_filemap(const vector<file_t>& files, const vector<free_t>& frees, size_t total_blocks) {
  string filemap {string(total_blocks, '.')};

  for (const auto[pos, id, size] : files) {
    for (int i = 0; i < size; i++) {
      filemap[pos + i] = static_cast<char>(id + 0x30);
    }
  }

  cout << filemap << endl;
}

int main() {
  // Parse input
  vector<file_t> files;
  vector<free_t> frees;
  
  string line;
  getline(cin, line);

  files.push_back(file_t(0, 0, line[0] - 0x30));
  size_t total_blocks{static_cast<size_t>(line[0] - 0x30)};

  for (size_t i = 1; i < line.length(); i += 2) {
    frees.push_back(free_t(total_blocks, line[i] - 0x30));
    total_blocks += line[i] - 0x30;

    files.push_back(file_t(total_blocks, (i+1)/2, line[i+1] - 0x30));
    total_blocks += line[i+1] - 0x30;
  }

  // Trying moving files from the right side
  for (size_t i = files.size() - 1; i > 0; --i) {
    auto[file_pos, file_id, file_size] {files[i]};
    // cout << i << ' ' << file_id << endl;

    // Search for leftmost free space which can fit the file
    for (size_t j = 0; j < frees.size(); j++) {
      auto[free_pos, free_size] {frees[j]};

      // Skip free space if can't fit
      if (free_size < file_size)
        continue;

      // Go to next file if reached to the right of file
      if (free_pos > file_pos)
        break;

      // cout << "Moving file " << file_id << " to free space @ index " << j << " and pos " << free_pos << endl;
      
      // Otherwise update the file to start at the free space position
      file_pos = free_pos;
      files[i] = file_t(file_pos, file_id, file_size);
      // Update free space to start from new position and have reduced size
      free_pos += file_size;
      free_size -= file_size;
      frees[j] = free_t(free_pos, free_size);
      break;
    }

  }

  // Compute Checksum
  size_t acc{0};

  for (const auto[pos, id, size] : files) {
    for (int i = 0; i < size; i++) {
      acc += (id * (pos + i));
    }
  }

  cout << acc << endl;

  return 0;
}
