#ifndef MOCK_C_API_H_
#define MOCK_C_API_H_

#include "c_api.h"
#include "trompeloeil.hpp"

class API
{
public:
  MAKE_MOCK3(c_api_func1, int(c_api_cookie*, const char*, int));
  MAKE_MOCK1(c_api_func2, int(int));
  MAKE_MOCK1(c_api_end, void(c_api_cookie*));
};

extern API c_api_mock;

#endif // MOCK_C_API_H_