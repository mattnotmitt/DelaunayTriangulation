cmake_minimum_required(VERSION 3.12)
project(DelauneyTriangulation)
Include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "--coverage")

enable_testing()
add_subdirectory(external)

add_library(DTLib src/Mesh.cpp src/Mesh.hpp src/Vertex.cpp src/Vertex.hpp src/Triangle.cpp src/Triangle.hpp src/utils.cpp  src/IMesh.hpp src/Vec.hpp src/Vec.cpp)
target_link_libraries(DTLib Eigen3::Eigen)

add_executable(DTTestExec tests/tests.cpp tests/test_mesh.cpp tests/test_vertex.cpp tests/test_triangle.cpp tests/test_utils.cpp)
target_link_libraries(DTTestExec DTLib Catch2::Catch2 Eigen3::Eigen)

add_custom_target(build-time-make-data-directory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory data)

add_test(DTTest DTTestExec)