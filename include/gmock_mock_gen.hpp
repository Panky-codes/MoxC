#ifndef GMOCK_MOCK_GEN_HPP
#define GMOCK_MOCK_GEN_HPP

#include "Imock_gen.hpp"

#include "data_types.hpp"
#include "string"

class GmockMockGen : public IMockGen {
public:
  explicit GmockMockGen(std::string_view file_name,
                             std::string_view dest_path);
  void genMockHeader(const std::vector<func_info_t> &func_info) override;
  void genMockImpl(const std::vector<func_info_t> &func_info) override;

private:
  std::string_view m_file_name;
  std::string_view m_dest_path;
};

#endif // GMOCK_MOCK_GEN_HPP
