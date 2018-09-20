#pragma once

#include <vector>

#include "solver.h"
#include "../board.h"

namespace cheapmon::sudoku::solver {

class greedy_solver : solver {
 public:
  greedy_solver() = delete;
  ~greedy_solver() override = delete;
  static board solve(const board &array);
 private:
  static void erase_squares(board &array);
  static void erase_square(std::vector<value> &square, const std::vector<int> &values);
  static void erase_by_row(board &array);
  static void erase_by_col(board &array);
  static void erase_by_block(board &array);
};

}