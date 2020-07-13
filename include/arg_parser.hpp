#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP
// Own header
#include "data_types.hpp"

// System header
#include <tuple>

// Third-party header
#include "argparse/argparse.hpp"

class ArgParser {
public:
  explicit ArgParser(const std::string &exe_name);
  void parseArgs(int argc, char *argv[]); // NOLINT
  void configureArgs();
  void validate_args() const;
  [[nodiscard]] std::string getFileName() const noexcept;
  [[nodiscard]] std::string getDestLocation() const noexcept;
  [[nodiscard]] argparse::ArgumentParser getArgParser() const noexcept;
  [[nodiscard]] mock_gen_t getMockFramework() const noexcept;
  [[nodiscard]] std::tuple<mock_gen_t, std::string, std::string>
  getArgValues() const noexcept;

private:
  std::string m_file_name;
  std::string m_dest_loc;
  mock_gen_t m_mock_framework;
  std::map<std::string_view, mock_gen_t> m_mock_map{
      {"gmock", mock_gen_t::Gmock}, {"trom", mock_gen_t::Tromeloeil}};
  argparse::ArgumentParser m_program;
};

#endif // ARG_PARSER_HPP