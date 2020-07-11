// Own header
#include "trompeloeil_mock_gen.hpp"
#include "data_types.hpp"
#include "file_parser.hpp"

// System header
#include <algorithm>
#include <fstream>
#include <numeric>
#include <string>
#include <vector>

// Third-party header
#include "fmt/format.h"

// Static functions
static std::string str_toupper(std::string_view s) {
  std::string ret_str(s);
  std::transform(s.begin(), s.end(), ret_str.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return ret_str;
}

TromeloeilMockGen::TromeloeilMockGen(std::string_view interface_file,
                                     std::string_view dest_path)
    : m_dest_path{dest_path} {
  // TODO: Should make it cross platform for Windows later
  // If the interface_file looks like this => ../hello.h
  // Then first step gets the => hello.h
  // Second step separates the file name and determines type
  // It will throw an exception in generateMocks function if the header is
  // invalid
  const std::string_view delimiter = "/";
  const auto split_point = [&interface_file, &delimiter]() {
    auto loc = interface_file.find_last_of(delimiter);
    return (loc == std::string_view::npos) ? 0 : (loc + 1);
  }();
  const auto sub_str_len = interface_file.size() - split_point;
  const auto file_name_w_ext = interface_file.substr(split_point, sub_str_len);

  const std::string_view dot = ".";
  const auto dot_loc = [&file_name_w_ext, &dot]() {
    auto loc = file_name_w_ext.find_last_of(dot);
    return (loc == std::string_view::npos) ? 0 : (loc);
  }();
  m_file_type =
      (file_name_w_ext.substr(dot_loc + 1, file_name_w_ext.size()) == "h")
          ? file_type_t::C_HEADER
          : file_type_t::UNKNOWN_TYPE;
  m_file_name = (m_file_type == file_type_t::C_HEADER)
                    ? interface_file.substr(split_point, dot_loc)
                    : "";
}

void TromeloeilMockGen::genMockHeader(
    const std::vector<func_info_t> &func_info) {
  if (m_file_type == file_type_t::UNKNOWN_TYPE) {
    throw std::invalid_argument("The given file type is not valid");
  }
  std::ofstream file_header(fmt::format("mock_{}.hpp", m_file_name));
  std::string out;
  out += fmt::format("#ifndef MOCK_{}_HPP_ \n", str_toupper(m_file_name));
  out += fmt::format("#define MOCK_{}_HPP_ \n\n", str_toupper(m_file_name));
  out += fmt::format("#include \"{}.h\" \n", m_file_name);
  out += fmt::format("#include <trompeloeil.hpp> \n\n");

  out += fmt::format("class mock_{}_t {{ \n public: \n", m_file_name);
  for (const auto &elem : func_info) {
    out += fmt::format("  MAKE_MOCK{0}({1},{2}({3})); \n",
                       elem.args_type.size(), elem.funcName, elem.retType,
                       fmt::join(elem.args_type, ", "));
  }

  out += fmt::format("}}; \n\n");

  out += fmt::format("extern mock_{0}_t {0}_mock; \n\n", m_file_name);
  out += fmt::format("#endif // MOCK_{}_HPP_ \n", str_toupper(m_file_name));
  file_header.write(out.c_str(), static_cast<long>(out.size()));
  file_header.close();
}
void TromeloeilMockGen::genMockImpl(const std::vector<func_info_t> &func_info) {
  if (m_file_type == file_type_t::UNKNOWN_TYPE) {
    throw std::invalid_argument("The given file type is not valid");
  }

  std::ofstream file_header(fmt::format("mock_{}.cpp", m_file_name));
  std::string out;
  out += fmt::format("#include \"mock_{}.hpp\" \n\n", m_file_name);

  out += fmt::format("mock_{0}_t {0}_mock;\n\n", m_file_name);
  out += fmt::format("extern \"C\" {{ \n");
  for (const auto &elem : func_info) {
    std::vector<std::string> param_list(elem.args_type.size());

    std::transform(elem.args_name.begin(), elem.args_name.end(),
                   elem.args_type.begin(), param_list.begin(),
                   [](std::string_view arg_name, std::string_view param_type) {
                     return fmt::format("{0} {1}", param_type, arg_name);
                   });

    out += fmt::format("  {0} {1}({2}) {{ \n", elem.retType, elem.funcName,
                       fmt::join(param_list, ", "));

    out += fmt::format("      return {0}_mock.{1}({2});\n", m_file_name,
                       elem.funcName, fmt::join(elem.args_name, ", "));
    out += fmt::format("      }} \n\n");
  }
  out += fmt::format("}}; \n\n");

  file_header.write(out.c_str(), static_cast<long>(out.size()));
  file_header.close();
}
