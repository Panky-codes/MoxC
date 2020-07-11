#include "mock_c_api.hpp" 

mock_c_api_t c_api_mock;

extern "C" { 
  int c_api_func1(struct c_api_cookie * arg_0, const char * arg_1, int arg_2) { 
      return c_api_mock.c_api_func1(arg_0, arg_1, arg_2);
      } 

  int c_api_func2(int arg_0) { 
      return c_api_mock.c_api_func2(arg_0);
      } 

  void c_api_end(struct c_api_cookie * arg_0) { 
      return c_api_mock.c_api_end(arg_0);
      } 

}; 

