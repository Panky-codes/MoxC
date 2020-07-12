#ifndef FILE_PARSER_HPP_
#define FILE_PARSER_HPP_

#include <data_types.hpp>
#include <string>
#include <vector>

[[nodiscard]] std::vector<func_info_t>
parseFunctionFromFile(const std::string &fileName);
[[nodiscard]] std::string_view parseFileInfo(std::string_view interface_file);
void _helperPrintFunctionFromFile(const std::string &fileName);

#endif // FILE_PARSER_HPP_
