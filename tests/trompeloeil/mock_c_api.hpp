#ifndef MOCK_C_API_HPP_ 
#define MOCK_C_API_HPP_ 

#include "c_api.h" 
#include <trompeloeil.hpp> 

class mock_c_api_t { 
 public: 
  MAKE_MOCK1(c_api_end,void(struct c_api_cookie *)); 
  MAKE_MOCK3(c_api_func1,int(struct c_api_cookie *, const char *, int)); 
  MAKE_MOCK1(c_api_func2,int(int)); 
}; 

extern mock_c_api_t c_api_mock; 

#endif // MOCK_C_API_HPP_ 
