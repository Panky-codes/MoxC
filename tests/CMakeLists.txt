include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests)
#include_directories(${CMAKE_SOURCE_DIR}/tests/trompeloeil)

add_library(catch_main STATIC tests-main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

add_library(mock_c_api_trom STATIC Trompeloeil/mock_c_api.cpp)
target_link_libraries(mock_c_api_trom PUBLIC CONAN_PKG::trompeloeil)

add_library(mock_c_api_gmock STATIC Gmock/mock_c_api.cpp)
target_link_libraries(mock_c_api_gmock PUBLIC CONAN_PKG::gtest)

add_library(client_c_api_trom STATIC client_c_api.cpp)
target_link_libraries(client_c_api_trom PRIVATE mock_c_api_trom)

add_library(client_c_api_gmock STATIC client_c_api.cpp)
target_link_libraries(client_c_api_gmock PRIVATE mock_c_api_gmock)

add_executable(test_trom tests-trompeloeil.cpp)
target_link_libraries(test_trom PUBLIC client_c_api_trom project_options catch_main CONAN_PKG::trompeloeil)
catch_discover_tests(test_trom)

add_executable(test_gmock tests-gmock.cpp)
target_link_libraries(test_gmock PUBLIC client_c_api_gmock project_options catch_main CONAN_PKG::gtest)
catch_discover_tests(test_gmock)

set_target_properties(test_gmock test_trom mock_c_api_gmock client_c_api_trom mock_c_api_trom catch_main PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)
