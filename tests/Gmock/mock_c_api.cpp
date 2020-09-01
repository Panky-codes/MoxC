#include "mock_c_api.hpp" 

static mock_c_api_t* local_ptr_to_impl = nullptr;
mock_c_api_t::mock_c_api_t() { local_ptr_to_impl = this; }
mock_c_api_t::~mock_c_api_t() { local_ptr_to_impl = nullptr; }

extern "C" { 
  int c_api_end(struct c_api_cookie arg_0) { 
      return local_ptr_to_impl->c_api_end(arg_0);
      } 

  int c_api_front(c_api_var_t var_struct) { 
      return local_ptr_to_impl->c_api_front(var_struct);
      } 

  int c_api_func1(struct c_api_cookie * cookie, const char * str, int len) { 
      return local_ptr_to_impl->c_api_func1(cookie, str, len);
      } 

  int c_api_func2(int len) { 
      return local_ptr_to_impl->c_api_func2(len);
      } 

}; 
