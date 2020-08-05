// Own header
#include "arg_parser.hpp"
#include "data_types.hpp"

// System header

// Third-party header
#include "argparse/argparse.hpp"

ArgParser::ArgParser(const std::string &exe_name)
    : m_mock_framework{mock_gen_t::Gmock}, m_program{argparse::ArgumentParser(
                                                 exe_name)} {}

void ArgParser::configureArgs() {
  m_program.add_argument("InterfaceFile").help("C Interface file");
  m_program.add_argument("-d", "--dest")
      .help("Destination folder for the generated mock files")
      .default_value(std::string("."));
  m_program.add_argument("-m", "--mock")
      .help("Available Mock generation framework:"
            "\n\t\t- \"gmock\" for GMock framework (default)"
            "\n\t\t- \"trom\" for Trompeloeil framework")
      .default_value(std::string("gmock"));
}

void ArgParser::parseArgs(int argc, char *argv[]) { // NOLINT
  m_program.parse_args(argc, argv);
  m_file_name = m_program.get<std::string>("InterfaceFile");
  m_dest_loc = m_program.get<std::string>("--dest");
  const auto mock_framework = m_program.get<std::string>("--mock");
  if (m_mock_map.find(mock_framework) != m_mock_map.end()) {
    m_mock_framework = m_mock_map[mock_framework];
  } else {
    throw std::runtime_error("Not a valid mock framework option!");
  }
}

std::string ArgParser::getFileName() const noexcept { return m_file_name; }
std::string ArgParser::getDestLocation() const noexcept { return m_dest_loc; }
mock_gen_t ArgParser::getMockFramework() const noexcept {
  return m_mock_framework;
}
std::tuple<mock_gen_t, std::string, std::string>
ArgParser::getArgValues() const noexcept {
  return {m_mock_framework, m_file_name, m_dest_loc};
}

argparse::ArgumentParser ArgParser::getArgParser() const noexcept {
  return m_program;
}
