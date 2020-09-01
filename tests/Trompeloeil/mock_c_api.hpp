#ifndef MOCK_C_API_HPP_ 
#define MOCK_C_API_HPP_ 

#include "c_api.h" 
#include <trompeloeil.hpp> 

class mock_c_api_t { 
 public: 
  MAKE_MOCK1(c_api_end,int(struct c_api_cookie)); 
  MAKE_MOCK1(c_api_front,int(c_api_var_t)); 
  MAKE_MOCK3(c_api_func1,int(struct c_api_cookie *, const char *, int)); 
  MAKE_MOCK1(c_api_func2,int(int)); 
}; 

#endif // MOCK_C_API_HPP_ 
