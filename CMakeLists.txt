cmake_minimum_required(VERSION 3.15)
project(DelauneyTriangulation)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "--coverage")

enable_testing()
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
add_subdirectory(external)
add_executable(DT src/Mesh.cpp src/Mesh.hpp tests/tests.cpp tests/test_mesh.cpp tests/test_vertex.cpp tests/test_triangle.cpp src/Vertex.cpp src/Vertex.hpp src/Triangle.cpp src/Triangle.hpp src/utils.cpp tests/test_utils.cpp src/IMesh.hpp)
target_link_libraries(DT Catch Eigen3::Eigen)
add_test(DTTest DT)