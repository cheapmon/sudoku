#pragma once

#include <array>
#include <vector>

namespace cheapmon::sudoku {

struct value {
 public:
  int v = 0;
  bool fixed = false;
  value(int i) : v(i), fixed(false) {}
  value(int i, bool f) : v(i), fixed(f) {}
  bool operator==(const value &other) const {
    return v == other.v && fixed == other.fixed;
  }
  bool operator!=(const value &other) const {
    return v != other.v || fixed != other.fixed;
  }
};

class board {
 public:
  explicit board(const std::array<int, 81> &puzzle);
  bool operator==(const board &other) const;
  bool operator!=(const board &other) const;
  std::string to_str(const bool &all = false);
  std::vector<value> &operator[](const int &i);
  int empty_squares();
  int faulty_squares();
  int next_square();
  bool correct();
 private:
  std::array<std::vector<value>, 81> array;
};

}