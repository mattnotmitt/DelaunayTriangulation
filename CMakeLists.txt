cmake_minimum_required(VERSION 3.12)
project(DelauneyTriangulation)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "--coverage")

include_directories(external)
add_executable(DT src/Mesh.cpp src/Mesh.hpp tests/tests.cpp tests/test_mesh.cpp tests/test_vertex.cpp tests/test_triangle.cpp src/Vertex.cpp src/Vertex.hpp src/Triangle.cpp src/Triangle.hpp src/utils.cpp tests/test_utils.cpp src/IMesh.hpp src/Vec.hpp src/Vec.cpp)