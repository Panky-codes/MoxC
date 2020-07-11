#include "mock_c_api.hpp" 

mock_c_api_t c_api_mock;

extern "C" { 
  void c_api_end(struct c_api_cookie * cookie) { 
      return c_api_mock.c_api_end(cookie);
      } 

  int c_api_func1(struct c_api_cookie * cookie, const char * str, int len) { 
      return c_api_mock.c_api_func1(cookie, str, len);
      } 

  int c_api_func2(int len) { 
      return c_api_mock.c_api_func2(len);
      } 

}; 

