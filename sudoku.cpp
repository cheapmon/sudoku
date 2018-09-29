#include <array>
#include <chrono>
#include <future>
#include <iostream>
#include <sstream>

#include "board.h"
#include "util.h"
#include "solver/greedy_solver.h"
#include "solver/recursive_solver.h"

using namespace cheapmon::sudoku;
using namespace std::chrono;

std::string evaluate(const board &puzzle) {
  std::stringstream out;
  board solution(solver::greedy_solver::solve(puzzle));
  std::pair result = solver::recursive_solver::solve(solution);
  if (result.first && result.second.correct()) {
    out << result.second.to_str() << std::endl;
  } else {
    out << result.second.to_str() << std::endl
        << "No possible solution." << std::endl;
  }
  return out.str();
}

int main(int argc, char *argv[]) {
  if (argc == 1 || argc > 2) {
    std::cout << "Please supply one puzzle file." << std::endl;
    return 0;
  }
  std::vector<board> puzzles = read_file(argv[1]);
  auto begin_time = high_resolution_clock::now();
  std::vector<std::future<std::string>> results;
  results.reserve(puzzles.size());
  for (const auto &puzzle : puzzles) {
    results.emplace_back(std::async(evaluate, puzzle));
  }
  for (auto &res : results) {
    std::cout << res.get();
  }
  auto time = duration_cast<microseconds>(high_resolution_clock::now() - begin_time);
  std::cout << "Finished in " << ((double) time.count()) / 1000.0 << " milliseconds." << std::endl;
}