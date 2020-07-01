include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(lib SHARED lib.cpp)
target_link_libraries(
      lib PRIVATE CONAN_PKG::fmt project_warnings project_options)

add_executable(main_process main.cpp)
target_link_libraries(
      main_process PRIVATE lib project_warnings project_options)

set_target_properties(lib main_process PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)



