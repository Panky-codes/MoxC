#include "client_c_api.hpp"

#include "c_api.h"

int test_call(int x) {
  // Retunrs the square of the int
  return c_api_func2(x);
}