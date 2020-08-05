#include "catch2/catch.hpp"
#include "trompeloeil.hpp"

#include "client_c_api.hpp"
#include "mock_c_api.hpp"

using trompeloeil::_;

mock_c_api_t c_api_mock;

TEST_CASE("Checking Trompeloeil mocks") {
  SECTION("FUNC2") {
    REQUIRE_CALL(c_api_mock, c_api_func2(2)).RETURN(4);
    REQUIRE(test_func2(2) == 4);
  }
  SECTION("FUNC_END") {
    int var1 = 10;
    float var2 = 20.0;
    REQUIRE_CALL(c_api_mock, c_api_end(_)).RETURN(10);
    REQUIRE(test_func_end(var1, var2) == 20);
  }
}
