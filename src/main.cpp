// Own header
#include "data_types.hpp"
#include "file_parser.hpp"
#include "trompeloeil_mock_gen.hpp"

// System header
#include <memory>
// Third-party header
#include "argparse/argparse.hpp"
#include "fmt/format.h"

int main(int argc, char *argv[]) {
  // Should use argparse here
  argparse::ArgumentParser program(
      "MoxC - C Mock generator for multiple frameworks");
  program.add_argument("InterfaceFile").help("C Interface file");
  program.add_argument("-d", "--dest")
      .help("Destination folder for the generated mock files")
      .default_value(std::string("."));
  program.add_argument("-m", "--mock")
      .help("Available Mock generation framework:"
            "\n\t\t- Option \"gmock\" for GMock framework "
            "\n\t\t- Option \"trom\" for Trompeloeil framework")
      .default_value(std::string("trom"));

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }
  auto interface_file = program.get<std::string>("InterfaceFile");
  auto dest_loc = program.get<std::string>("--dest");

  try {
    auto func_info = parseFunctionFromFile(interface_file);
    const auto file_name = parseFileMetaData(interface_file);
    std::unique_ptr<IMockGen> mock_gen =
        std::make_unique<TromeloeilMockGen>(file_name, dest_loc);
    mock_gen->genMockHeader(func_info);
    mock_gen->genMockImpl(func_info);
  } catch (const std::exception &e) {
    fmt::print(stderr, "{}\n", e.what());
    exit(0);
  }
  return 0;
}
