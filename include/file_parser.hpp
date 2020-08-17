#ifndef FILE_PARSER_HPP_
#define FILE_PARSER_HPP_

#include <data_types.hpp>
#include <string>
#include <vector>

class FileParser {
public:
  explicit FileParser(std::string full_file_name);
  [[nodiscard]] std::vector<func_info_t>
  parseFunctionInfo();
  [[nodiscard]] std::pair<std::string_view, file_type_t>
  getFileMetaData();

private:
  void _helperPrintFunctionFromFile(const std::string &fileName);
  std::string m_full_file_name;
  std::string m_file_name{};
  file_type_t m_file_type{file_type_t::UNKNOWN_TYPE};
};
#endif // FILE_PARSER_HPP_
