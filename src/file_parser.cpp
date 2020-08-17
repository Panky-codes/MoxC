// Own header
#include "file_parser.hpp"
#include "data_types.hpp"

// System header
#include <iostream>
#include <string>
#include <vector>

// Third-party header
#include "fmt/format.h"
#include <clang-c/Index.h>

using namespace std;
ostream &operator<<(ostream &stream, const CXString &str) {
  stream << clang_getCString(str);
  clang_disposeString(str);
  return stream;
}

static std::string get_string(const CXString &str) {
  std::string cppStr = clang_getCString(str);
  clang_disposeString(str);
  return cppStr;
}

FileParser::FileParser(std::string full_file_name)
    : m_full_file_name{std::move(full_file_name)} {}

std::vector<func_info_t>
FileParser::parseFunctionInfo() {
  std::vector<func_info_t> m_parseFunc;
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit unit = clang_parseTranslationUnit(
      index, m_full_file_name.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);
  if (unit == nullptr) {
    throw std::invalid_argument(
        "Unable to parse translation unit. Give a valid .h C header file");
  }
  CXCursor cursor = clang_getTranslationUnitCursor(unit);

  clang_visitChildren(
      cursor,
      [](CXCursor c, CXCursor parent, CXClientData client_data) { // NOLINT
        auto &parseFunc = *reinterpret_cast<std::vector<func_info_t> *>(
            client_data); // NOLINT As it is a C i/f
        if (clang_getCursorKind(c) == CXCursorKind::CXCursor_FunctionDecl) {
          func_info_t func_info;
          func_info.funcName = get_string(clang_getCursorSpelling(c));
          auto no_of_arg =
              static_cast<unsigned int>(clang_Cursor_getNumArguments(c));
          for (unsigned int i = 0; i < no_of_arg; ++i) {
            auto arg = clang_Cursor_getArgument(c, i);
            auto arg_cursor_type = clang_getCursorType(arg);
            func_info.args_type.push_back(
                get_string(clang_getTypeSpelling(arg_cursor_type)));
            const auto arg_str = [&arg, i]() {
              const auto str = get_string(clang_getCursorSpelling(arg));
              return (empty(str)) ? fmt::format("arg_{}", i) : str;
            }();
            func_info.args_name.push_back(arg_str);
          }

          auto ret_type = clang_getResultType(clang_getCursorType(c));
          func_info.retType = get_string(clang_getTypeSpelling(ret_type));
          parseFunc.push_back(std::move(func_info));
        }
        return CXChildVisit_Recurse;
      },
      &m_parseFunc);

  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);
  return m_parseFunc;
}

std::pair<std::string_view, file_type_t>
FileParser::getFileMetaData() {
  // TODO: Should make it cross platform for Windows later
  // If the m_full_file_name looks like this => ../hello.h
  // Then first step gets the => hello.h
  // Second step separates the file name and determines type
  // It will throw an exception in generateMocks function if the header is
  // invalid
  const std::string_view delimiter = "/";
  const auto split_point = [&]() {
    auto loc = m_full_file_name.find_last_of(delimiter);
    return (loc == std::string_view::npos) ? 0 : (loc + 1);
  }();
  const auto sub_str_len = m_full_file_name.size() - split_point;
  const auto file_name_w_ext = m_full_file_name.substr(split_point, sub_str_len);

  const std::string_view dot = ".";
  const auto dot_loc = [&file_name_w_ext, &dot]() {
    auto loc = file_name_w_ext.find_last_of(dot);
    return (loc == std::string_view::npos) ? 0 : (loc);
  }();

  const auto extention =
      file_name_w_ext.substr(dot_loc + 1, file_name_w_ext.size());
  if (extention == "h") {
    m_file_type = file_type_t::C_HEADER;
  } else if (extention == "hpp") {
    m_file_type = file_type_t::CPP_HEADER;
  } else {
    m_file_type = file_type_t::UNKNOWN_TYPE;
  }

  if (m_file_type == file_type_t::UNKNOWN_TYPE) {
    throw std::invalid_argument(
        "The given file type is not valid! Give valid .h C header file");
  }
  m_file_name = (m_file_type != file_type_t::UNKNOWN_TYPE)
                    ? m_full_file_name.substr(split_point, dot_loc)
                    : "";

  return {m_file_name, m_file_type};
}
