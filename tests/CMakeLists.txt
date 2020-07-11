include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tests)
include_directories(${CMAKE_SOURCE_DIR}/tests/trompeloeil)

add_library(catch_main STATIC tests-main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

add_library(mock_c_api STATIC trompeloeil/mock_c_api1.cpp)
target_link_libraries(mock_c_api PUBLIC CONAN_PKG::trompeloeil)

add_library(client_c_api STATIC client_c_api.cpp)
target_link_libraries(client_c_api PRIVATE mock_c_api)

add_executable(test_client tests-client-c-api.cpp)
target_link_libraries(test_client PUBLIC client_c_api project_options catch_main CONAN_PKG::trompeloeil)
catch_discover_tests(test_client)

set_target_properties(test_client client_c_api mock_c_api catch_main PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)
