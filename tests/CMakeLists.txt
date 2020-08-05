include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests)
include_directories(${CMAKE_SOURCE_DIR}/tests/trompeloeil)

add_library(catch_main STATIC tests-main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

add_library(mock_c_api_trom STATIC trompeloeil/mock_c_api.cpp)
target_link_libraries(mock_c_api_trom PUBLIC CONAN_PKG::trompeloeil)

add_library(mock_c_api_gmock STATIC gmock/mock_c_api.cpp)
target_link_libraries(mock_c_api_gmock PUBLIC CONAN_PKG::gtest)

add_library(client_c_api STATIC client_c_api.cpp)
target_link_libraries(client_c_api PRIVATE mock_c_api_trom)

add_executable(test_client tests-trompeloeil.cpp)
target_link_libraries(test_client PUBLIC client_c_api project_options catch_main CONAN_PKG::trompeloeil)
catch_discover_tests(test_client)

set_target_properties(test_client mock_c_api_gmock client_c_api mock_c_api_trom catch_main PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)
