#ifndef DATA_TYPES_HPP_
#define DATA_TYPES_HPP_

#include <string>
#include <vector>

struct func_info_t {
  std::string retType{};
  std::vector<std::string> args_type{};
  std::vector<std::string> args_name{};
  std::string funcName{};
};

enum class file_type_t {
  C_HEADER,
  UNKNOWN_TYPE
};

#endif // DATA_TYPES_HPP_
