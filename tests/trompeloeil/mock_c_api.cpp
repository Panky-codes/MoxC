// unit-test_c_api.cpp
#include "mock_c_api.h"

API c_api_mock;

extern "C" {
int c_api_func1(c_api_cookie *cookie, const char *str, int len) {
  return c_api_mock.c_api_func1(cookie, str, len);
}

int c_api_func2(int len) { return c_api_mock.c_api_func2(len); }

void c_api_end(c_api_cookie *cookie) { c_api_mock.c_api_end(cookie); }
}
