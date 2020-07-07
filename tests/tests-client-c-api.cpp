#include "catch2/catch.hpp"
#include "trompeloeil.hpp"

#include "client_c_api.hpp"
#include "mock_c_api.h"

TEST_CASE("DUMMY TEST") {
  REQUIRE_CALL(c_api_mock, c_api_func2(2)).RETURN(4);
  REQUIRE(test_call(2) == 4);
}
