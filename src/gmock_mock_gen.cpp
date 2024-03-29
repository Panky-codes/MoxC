// Own header
#include "gmock_mock_gen.hpp"
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

// TODO:
// should the extern be in the mock.cpp file ?

// Static functions
static std::string str_toupper(std::string_view s) {
  std::string ret_str(s);
  std::transform(s.begin(), s.end(), ret_str.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  return ret_str;
}

GmockMockGen::GmockMockGen(std::string_view file_name,
                           std::string_view dest_path)
    : m_file_name{file_name}, m_dest_path{dest_path} {}

void GmockMockGen::genMockHeader(const std::vector<func_info_t> &func_info) {

  std::ofstream file_header(
      fmt::format("{0}/mock_{1}.hpp", m_dest_path, m_file_name));
  if (file_header.fail()) {
    throw std::ios_base::failure(
        fmt::format("Unable to create file: mock_{}.hpp", m_file_name));
  }
  std::string out;
  out += fmt::format("#ifndef MOCK_{}_HPP_ \n", str_toupper(m_file_name));
  out += fmt::format("#define MOCK_{}_HPP_ \n\n", str_toupper(m_file_name));
  out += fmt::format("#include \"{}.h\" \n", m_file_name);
  out += fmt::format("#include <gmock/gmock.h> \n\n");

  out += fmt::format("class mock_{}_t {{ \n public: \n", m_file_name);
  out += fmt::format("  mock_{}_t();", m_file_name);
  out += fmt::format("  ~mock_{}_t();", m_file_name);
  for (const auto &elem : func_info) {
    out += fmt::format("  MOCK_METHOD({0}, {1},({2})); \n", elem.retType,
                       elem.funcName, fmt::join(elem.args_type, ", "));
  }

  out += fmt::format("}}; \n\n");
  out +=
      fmt::format("using nice_mock_{0}_t = ::testing::NiceMock<mock_{0}_t>;\n",
                  m_file_name);
  out += fmt::format(
      "using strict_mock_{0}_t = ::testing::StrictMock<mock_{0}_t>;\n\n",
      m_file_name);

  out += fmt::format("#endif // MOCK_{}_HPP_ \n", str_toupper(m_file_name));
  file_header.write(out.c_str(), static_cast<long>(out.size()));
  file_header.close();
}

void GmockMockGen::genMockImpl(const std::vector<func_info_t> &func_info) {
  std::ofstream file_body(
      fmt::format("{0}/mock_{1}.cpp", m_dest_path, m_file_name));
  if (file_body.fail()) {
    throw std::ios_base::failure(
        fmt::format("Unable to create file: mock_{}.hpp", m_file_name));
  }
  std::string out;
  out += fmt::format("#include \"mock_{}.hpp\" \n\n", m_file_name);
  out += fmt::format("static mock_{0}_t* local_ptr_to_impl = nullptr;\n",
                     m_file_name);
  out +=
      fmt::format("mock_{0}_t::mock_{0}_t() {{ local_ptr_to_impl = this; }}\n",
                  m_file_name);
  out += fmt::format(
      "mock_{0}_t::~mock_{0}_t() {{ local_ptr_to_impl = nullptr; }}\n\n",
      m_file_name);

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

    out += fmt::format("      return local_ptr_to_impl->{0}({1});\n",
                       elem.funcName, fmt::join(elem.args_name, ", "));
    out += fmt::format("      }} \n\n");
  }
  out += fmt::format("}}; \n");

  file_body.write(out.c_str(), static_cast<long>(out.size()));
  file_body.close();
}
