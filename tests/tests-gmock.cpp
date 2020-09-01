#include "catch2/catch.hpp"
#include <gmock/gmock.h>

#include "client_c_api.hpp"
#include "Gmock/mock_c_api.hpp"

using ::testing::_;
using ::testing::Return;

TEST_CASE("Checking GMOCK mocks") {
  nice_mock_c_api_t c_api_mock;
  SECTION("FUNC2") {
    EXPECT_CALL(c_api_mock, c_api_func2(2)).WillOnce(Return(4));
    REQUIRE(test_func2(2) == 4);
  }
  SECTION("FUNC_END") {
    int var1 = 10;
    float var2 = 20.0;
    EXPECT_CALL(c_api_mock, c_api_end(_)).WillOnce(Return(10));
    REQUIRE(test_func_end(var1, var2) == 20);
  }
}
