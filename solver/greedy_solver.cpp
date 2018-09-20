#include <algorithm>

#include "greedy_solver.h"

namespace cheapmon::sudoku::solver {

board greedy_solver::solve(const board &array) {
  board copy(array);
  board other(array);
  do {
    other = copy;
    erase_squares(copy);
  } while (other != copy);
  return copy;
}

void greedy_solver::erase_squares(board &array) {
  erase_by_row(array);
  erase_by_col(array);
  erase_by_block(array);
}

void greedy_solver::erase_by_row(board &array) {
  for (int row = 0; row < 9; row++) {
    std::vector<int> blocked_values;
    for (int col = 0; col < 9; col++) {
      const std::vector<value> &square = array[row * 9 + col];
      if (square.size() == 1 && square[0].fixed) {
        blocked_values.push_back(square[0].v);
      }
    }
    for (int col = 0; col < 9; col++) {
      erase_square(array[row * 9 + col], blocked_values);
    }
  }
}

void greedy_solver::erase_by_col(board &array) {
  for (int row = 0; row < 9; row++) {
    std::vector<int> blocked_values;
    for (int col = 0; col < 9; col++) {
      const std::vector<value> &square = array[col * 9 + row];
      if (square.size() == 1 && square[0].fixed) {
        blocked_values.push_back(square[0].v);
      }
    }
    for (int col = 0; col < 9; col++) {
      erase_square(array[col * 9 + row], blocked_values);
    }
  }
}

void greedy_solver::erase_by_block(board &array) {
  const std::array<int, 9> middle_squares = {10, 13, 16, 37, 40, 43, 64, 67, 70};
  const std::array<int, 9> offsets = {-10, -9, -8, -1, 0, 1, 8, 9, 10};
  for (int position : middle_squares) {
    std::vector<int> blocked_values;
    for (int offset : offsets) {
      const std::vector<value> &square = array[position + offset];
      if (square.size() == 1 && square[0].fixed) {
        blocked_values.push_back(square[0].v);
      }
    }
    for (int offset : offsets) {
      erase_square(array[position + offset], blocked_values);
    }
  }
}

void greedy_solver::erase_square(std::vector<value> &square, const std::vector<int> &values) {
  if (square.size() == 1) {
    return;
  }
  for (int value : values) {
    square.erase(std::remove_if(square.begin(), square.end(), [&value](struct value &v) {
      return v.v == value && !v.fixed;
    }), square.end());
  }
  if (square.size() == 1) {
    square[0].fixed = true;
  }
}

}