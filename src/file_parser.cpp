// Own header
#include "data_types.hpp"

// System header
#include <iostream>
#include <string>
#include <vector>

// Third-party header
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

void printFunctionFromFile(const std::string &fileName) {
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit unit = clang_parseTranslationUnit(
      index, fileName.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);
  if (unit == nullptr) {
    cerr << "Unable to parse translation unit. Quitting." << endl;
    exit(-1);
  }
  CXCursor cursor = clang_getTranslationUnitCursor(unit);
  clang_visitChildren(
      cursor,
      [](CXCursor c, CXCursor parent, CXClientData client_data) {
        if (clang_getCursorKind(c) == CXCursorKind::CXCursor_FunctionDecl) {
          func_info_t func_info;
          std::vector<CXCursor> args;
          cout << "Function name: " << clang_getCursorSpelling(c) << "\n";

          auto no_of_arg =
              static_cast<unsigned int>(clang_Cursor_getNumArguments(c));
          for (unsigned int i = 0; i < no_of_arg; ++i) {
            args.push_back(clang_Cursor_getArgument(c, i));
          }
          cout << "Argument name: ";
          for (auto arg : args) {
            cout << clang_getTypeSpelling(clang_getCursorType(arg)) << ", ";
          }

          auto ret_type = clang_getResultType(clang_getCursorType(c));
          cout << "\n"
               << "Return type name: " << clang_getTypeSpelling(ret_type)
               << "\n";
          func_info.retType = get_string(clang_getTypeSpelling(ret_type));
        }
        return CXChildVisit_Recurse;
      },
      nullptr);

  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);
}

std::vector<func_info_t> parseFunctionFromFile(const std::string &fileName) {
  std::vector<func_info_t> m_parseFunc;
  CXIndex index = clang_createIndex(0, 0);
  CXTranslationUnit unit = clang_parseTranslationUnit(
      index, fileName.c_str(), nullptr, 0, nullptr, 0, CXTranslationUnit_None);
  if (unit == nullptr) {
    throw std::invalid_argument("Unable to parse translation unit. Quitting.");
  }
  CXCursor cursor = clang_getTranslationUnitCursor(unit);

  clang_visitChildren(
      cursor,
      [](CXCursor c, CXCursor parent, CXClientData client_data) {
        auto& parseFunc = *reinterpret_cast<std::vector<func_info_t>*>(client_data); 
        if (clang_getCursorKind(c) == CXCursorKind::CXCursor_FunctionDecl) {
          func_info_t func_info;
          func_info.funcName = get_string(clang_getCursorSpelling(c));
          auto no_of_arg =
              static_cast<unsigned int>(clang_Cursor_getNumArguments(c));
          for (unsigned int i = 0; i < no_of_arg; ++i) {
            auto arg_cursor_type =
                clang_getCursorType(clang_Cursor_getArgument(c, i));
            func_info.args.push_back(
                get_string(clang_getTypeSpelling(arg_cursor_type)));
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
