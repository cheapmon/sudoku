#pragma once

#include "../board.h"

namespace cheapmon::sudoku::solver {

class solver {
 public:
  solver() = delete;
  virtual ~solver() = delete;
  static board solve(const board &array) = delete;
};

}