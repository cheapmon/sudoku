#include <iostream>
#include <fstream>
#include <sstream>

#include "util.h"

namespace cheapmon::sudoku {

std::string value_vector_to_str(const std::vector<value> &values) {
  std::ostringstream stream;
  stream << "{";
  if (values.empty()) {
    stream << "}";
  } else if (values.size() == 1) {
    value val = values[0];
    stream << values[0].v;
    if (val.fixed) {
      stream << "F";
    }
    stream << "}";
  } else {
    for (unsigned long i = 0; i < values.size() - 1; i++) {
      value val = values[i];
      stream << val.v;
      if (val.fixed) {
        stream << "F";
      }
      stream << ", ";
    }
    value val = values[values.size() - 1];
    stream << val.v;
    if (val.fixed) {
      stream << "F";
    }
    stream << "}";
  }
  return stream.str();
}

std::vector<board> read_file(char path[]) {
  std::vector<board> puzzles;
  std::string line;
  std::string digit;
  std::ifstream file(path);
  if (file.is_open()) {
    while (std::getline(file, line)) {
      int pos = 0;
      std::array<int, 81> result{};
      std::istringstream stream(line);
      while (std::getline(stream, digit, ' ')) {
        result[pos] = std::stoi(digit);
        pos++;
      }
      puzzles.emplace_back(board(result));
    }
    file.close();
  }
  return puzzles;
}

}