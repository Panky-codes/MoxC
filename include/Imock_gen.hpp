#ifndef I_MOCK_GEN_HPP
#define I_MOCK_GEN_HPP

#include "data_types.hpp"

class IMockGen { //NOLINT
public:
  virtual void genMockHeader(const std::vector<func_info_t> &func_info) = 0;
  virtual void genMockImpl(const std::vector<func_info_t> &func_info) = 0;
  virtual ~IMockGen(){} //NOLINT
};

#endif // I_MOCK_GEN_HPP