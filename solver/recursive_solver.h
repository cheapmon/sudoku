#pragma once

#include "solver.h"

namespace cheapmon::sudoku::solver {

class recursive_solver : solver {
 public:
  recursive_solver() = delete;
  ~recursive_solver() override = delete;
  static std::pair<bool, board> solve(const board &array);
 private:
  static std::pair<bool, board> probe(const board &array, const int &pos, const int &val);
};

}