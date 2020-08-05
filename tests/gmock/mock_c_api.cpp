#include "mock_c_api.hpp" 

extern mock_c_api_t c_api_mock; 

extern "C" { 
  int c_api_end(struct c_api_cookie arg_0) { 
      return c_api_mock.c_api_end(arg_0);
      } 

  int c_api_front(c_api_var_t var_struct) { 
      return c_api_mock.c_api_front(var_struct);
      } 

  int c_api_func1(struct c_api_cookie * cookie, const char * str, int len) { 
      return c_api_mock.c_api_func1(cookie, str, len);
      } 

  int c_api_func2(int len) { 
      return c_api_mock.c_api_func2(len);
      } 
}; 