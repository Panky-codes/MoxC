// Own header
#include "data_types.hpp"
#include "file_parser.hpp"

// System header

// Third-party header
#include "fmt/format.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    fmt::print("No input!!");
    std::terminate();
  }
  parseFunctionFromFile(argv[1]);
  return 0;
}
