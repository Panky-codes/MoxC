#include "client_c_api.hpp"

#include "c_api.h"

int test_func2(int x) {
  // Retunrs the square of the int
  return c_api_func2(x);
}

int test_func_end(int var1, float var2) {
  struct c_api_cookie var_struct {0,};
  var_struct.var1 = var1;
  var_struct.var2 = var2;
  //do some calculation
  int calc_var = c_api_end(var_struct) + 10;
  return calc_var;
}