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

void parseFunctionFromFile(const std::string &fileName) {
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
        /* cout << "Cursor '" << clang_getCursorSpelling(c) << "' of kind '"
         */
        /*      << clang_getCursorKindSpelling(clang_getCursorKind(c)) */
        /*      << "'\n"; */

        if (clang_getCursorKind(c) == CXCursorKind::CXCursor_FunctionDecl) {
          std::vector<CXCursor> args;
          cout << "Function name: "
               << clang_getCursorSpelling(c)
               /* << "' of kind '" */
               /* << clang_getCursorKindSpelling(clang_getCursorKind(c)) */
               << "\n";
          auto no_of_arg = clang_Cursor_getNumArguments(c);
          for (int i = 0; i < no_of_arg; ++i) {
            args.push_back(clang_Cursor_getArgument(c, i));
          }
          auto arg1 = clang_getResultType(clang_getCursorType(c));
          /* cout << clang_getCursorSpelling(arg) << "    " << '\n' */
          cout << "Argument name: ";
          for (auto arg : args) {
            cout << clang_getTypeSpelling(clang_getCursorType(arg)) << ", ";
          }
          cout << "\n"
               << "Return type name: " << clang_getTypeSpelling(arg1) << "\n";
        }
        return CXChildVisit_Recurse;
      },
      nullptr);

  clang_disposeTranslationUnit(unit);
  clang_disposeIndex(index);
}
