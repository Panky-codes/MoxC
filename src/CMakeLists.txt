include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Clang REQUIRED)
add_library(file_parser SHARED file_parser.cpp)
target_link_libraries(
      file_parser PRIVATE libclang CONAN_PKG::fmt project_warnings project_options)

add_executable(main_process main.cpp)
target_link_libraries(
      main_process PRIVATE file_parser CONAN_PKG::fmt project_warnings project_options)

set_target_properties(file_parser main_process PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)



