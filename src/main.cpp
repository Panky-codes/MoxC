// Own header
#include "arg_parser.hpp"
#include "data_types.hpp"
#include "file_parser.hpp"
#include "gmock_mock_gen.hpp"
#include "trompeloeil_mock_gen.hpp"

// System header
#include <memory>

// Third-party header
#include "fmt/format.h"

// Static functions
static std::unique_ptr<IMockGen> makeMockGen(mock_gen_t mock_framework,
                                             std::string_view file_name,
                                             std::string_view dest_loc) {
  switch (mock_framework) {
  case mock_gen_t::Tromeloeil: {
    return std::make_unique<TromeloeilMockGen>(file_name, dest_loc);
  }
  case mock_gen_t::Gmock: {
    return std::make_unique<GmockMockGen>(file_name, dest_loc);
  }
  default: {
    throw std::invalid_argument("Not a valid mocking framework");
  }
  }
}

int main(int argc, char *argv[]) {
  ArgParser program("./moxc");
  try {
    program.configureArgs();
    program.parseArgs(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    std::cout << program.getArgParser();
    exit(0);
  }

  const auto [mock_framework, interface_file, dest_loc] =
      program.getArgValues();
  try {
    auto file_info = FileParser(interface_file);
    const auto func_info = file_info.parseFunctionInfo();
    const auto [file_name, _] = file_info.getFileMetaData();
    std::unique_ptr<IMockGen> mock_gen =
        makeMockGen(mock_framework, file_name, dest_loc);
    mock_gen->genMockHeader(func_info);
    mock_gen->genMockImpl(func_info);
  } catch (const std::exception &e) {
    fmt::print(stderr, "{}\n", e.what());
    exit(0);
  }
  return 0;
}