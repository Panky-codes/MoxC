#ifndef FILE_PARSER_HPP_
#define FILE_PARSER_HPP_

#include <data_types.hpp>
#include <string>
#include <vector>

[[nodiscard]] std::vector<func_info_t>
parseFunctionFromFile(const std::string &fileName);
void printFunctionFromFile(const std::string &fileName);

#endif // FILE_PARSER_HPP_
