#ifndef MOCK_C_API_HPP_ 
#define MOCK_C_API_HPP_ 

#include "c_api.h" 
#include <gmock/gmock.h>

class mock_c_api_t { 
 public: 
  virtual ~mock_c_api_t() = default;
  MOCK_METHOD(int, c_api_end,(struct c_api_cookie)); 
  MOCK_METHOD(int, c_api_front,(c_api_var_t)); 
  MOCK_METHOD(int, c_api_func1,(struct c_api_cookie *, const char *, int)); 
  MOCK_METHOD(int, c_api_func2, (int len));
}; 

#endif // MOCK_C_API_HPP_ 
