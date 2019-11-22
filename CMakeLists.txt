cmake_minimum_required(VERSION 3.15)
project(DelauneyTriangulation)

set(CMAKE_CXX_STANDARD 17)

include(CTest)

add_subdirectory(external)
add_executable(DTTest src/Mesh.cpp src/Mesh.hpp tests/tests.hpp tests/mesh.cpp src/Vertex.cpp src/Vertex.hpp src/Triangle.cpp src/Triangle.hpp)
target_link_libraries(DTTest Catch)