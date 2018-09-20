#pragma once

#include <array>
#include <string>
#include <vector>

#include "board.h"

namespace cheapmon::sudoku {

std::string value_vector_to_str(const std::vector<value> &values);
std::vector<board> read_file(char path[]);

}