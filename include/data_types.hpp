#ifndef DATA_TYPES_HPP_
#define DATA_TYPES_HPP_

#include <string>
#include <vector>

struct func_info_t {

  std::string retType{};
  std::vector<std::string> args{};
  std::string funcName{};
};

#endif // DATA_TYPES_HPP_
