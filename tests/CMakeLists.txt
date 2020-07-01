include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(catch_main STATIC tests-main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

add_executable(test_dummy tests-dummy.cpp)
target_link_libraries(test_dummy PUBLIC project_options catch_main)
catch_discover_tests(test_dummy)

set_target_properties(test_dummy catch_main PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
)
