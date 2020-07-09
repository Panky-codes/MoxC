include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(Clang REQUIRED)
add_library(file_parser SHARED file_parser.cpp)
target_link_libraries(
      file_parser PRIVATE libclang CONAN_PKG::fmt project_warnings project_options)

add_library(trompeloeil_mock_gen SHARED trompeloeil_mock_gen.cpp)
target_link_libraries(
      trompeloeil_mock_gen PRIVATE CONAN_PKG::fmt project_warnings project_options)

add_executable(main_process main.cpp)
target_link_libraries(
      main_process PRIVATE file_parser trompeloeil_mock_gen CONAN_PKG::fmt project_warnings project_options)

set_target_properties(file_parser main_process PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)



