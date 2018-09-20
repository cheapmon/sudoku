#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>

#include "util.h"

namespace cheapmon::sudoku {

board::board(const std::array<int, 81> &puzzle) {
  for (unsigned long i = 0; i < puzzle.size(); i++) {
    int square = puzzle[i];
    if (square == 0) {
      array[i] = std::vector<value>{1, 2, 3, 4, 5, 6, 7, 8, 9};
    } else {
      array[i] = std::vector<value>{value(square, true)};
    }
  }
}

bool board::operator==(const board &other) const {
  return array == other.array;
}

bool board::operator!=(const board &other) const {
  return array != other.array;
}

std::vector<value> &board::operator[](const int &i) {
  return array[i];
}

std::string board::to_str(const bool &all) {
  std::ostringstream stream;
  stream << "|";
  for (unsigned long i = 0; i < array.size(); i++) {
    if (all) {
      stream << value_vector_to_str(array[i]) << "|";
    } else {
      if (array[i].size() == 1) {
        stream << " " << array[i][0].v << " ";
      } else {
        stream << " _ ";
      }
      stream << "|";
    }
    if (i % 9 == 8 && i != 80) {
      stream << std::endl << "|";
    }
  }
  stream << std::endl;
  return stream.str();
}

int board::empty_squares() {
  return (int) std::count_if(std::begin(array), std::end(array), [](const std::vector<value> &square) {
    return square.size() > 1;
  });
}

int board::faulty_squares() {
  return (int) std::count_if(std::begin(array), std::end(array), [](const std::vector<value> &square) {
    return square.empty();
  });
}

int board::next_square() {
  for (unsigned long i = 0; i < array.size(); i++) {
    if (array[i].size() > 1) {
      return (int) i;
    }
  }
  return 0;
}

bool board::correct() {
  const std::array<int, 9> middle_squares = {10, 13, 16, 37, 40, 43, 64, 67, 70};
  const std::array<int, 9> offsets = {-10, -9, -8, -1, 0, 1, 8, 9, 10};
  const std::set<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> values;
  for (int row = 0; row < 9; row++) {
    values.clear();
    for (int col = 0; col < 9; col++) {
      values.insert(array[row * 9 + col][0].v);
    }
    if (numbers != values) {
      return false;
    }
  }
  for (int row = 0; row < 9; row++) {
    values.clear();
    for (int col = 0; col < 9; col++) {
      values.insert(array[col * 9 + row][0].v);
    }
    if (numbers != values) {
      return false;
    }
  }
  for (int pos : middle_squares) {
    values.clear();
    for (int offset : offsets) {
      values.insert(array[pos + offset][0].v);
    }
    if (numbers != values) {
      return false;
    }
  }
  return true;
}

}