// Own header
#include "data_types.hpp"
#include "file_parser.hpp"

// System header

// Third-party header
#include "fmt/format.h"

int main(int argc, char *argv[]) {
  // Should use argparse here
  if (argc == 1) {
    fmt::print(stderr, "No input!!\n");
    std::terminate();
  }

  try {
    auto func_info = parseFunctionFromFile(argv[1]);
    // printFunctionFromFile(argv[1]);
    fmt::print(stderr, "From the new parser ret!\n{0}\n",
               func_info.at(0).args.at(0));
  } catch (const std::exception &e) {
    fmt::print(stderr, "{}\n", e.what());
    std::abort();
  }
  return 0;
}
