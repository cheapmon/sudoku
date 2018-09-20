#include <iostream>

#include "greedy_solver.h"
#include "recursive_solver.h"

namespace cheapmon::sudoku::solver {

std::pair<bool, board> recursive_solver::solve(const board &array) {
  board copy(array);
  int pos = copy.next_square();
  for (const value &val : copy[pos]) {
    std::pair result = probe(copy, pos, val.v);
    if (result.first) {
      return result;
    }
  }
  return std::pair(false, array);
}

std::pair<bool, board> recursive_solver::probe(const board &array, const int &pos, const int &val) {
  board copy(array);
  copy[pos] = std::vector{value(val, true)};
  copy = greedy_solver::solve(copy);
  if (copy.faulty_squares() > 0) {
    return std::pair(false, copy);
  } else if (copy.empty_squares() == 0) {
    return std::pair(copy.correct(), copy);
  } else {
    int p = copy.next_square();
    for (const value &v : copy[p]) {
      std::pair result = probe(copy, p, v.v);
      if (result.first) {
        return result;
      }
    }
  }
  return std::pair(false, array);
}

}