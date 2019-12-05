#include <vector>
#include <catch/catch.hpp>
#include "../src/Vertex.hpp"
#include "../src/Mesh.hpp"

TEST_CASE("Default vertex is constructed", "[vertex][constructor]") {
    Vertex vec;
    REQUIRE(vec.getAttributes().empty());
    REQUIRE(vec.getVec().getX() == 0);
    REQUIRE(vec.getVec().getY() == 0);
    REQUIRE(vec.getVec().getZ() == 0);
    REQUIRE(vec.getIndex() == -1);
}

TEST_CASE("Vertex mutator functionality", "[vertex][mutator]") {
    // Coords excluded as requires valid mesh, is tested in other areas
    Vertex vec;
    vec.setIndex(100);
    std::vector<double> attr(5, 0.99);
    vec.setAttributes(attr);
    REQUIRE(vec.getAttributes().size() == 5);
    REQUIRE(vec.getIndex() == 100);
}

TEST_CASE("Test output stream operator", "[vertex][stream]") {
    Vertex vex;
    std::stringstream ss;
    ss << vex;
    REQUIRE(ss.str() == "(0, 0, 0)");
}

TEST_CASE("Test Equality", "[vertex][equality]") {
    Vertex vex, vex1;
    REQUIRE(vex == vex1);
    vex1.setIndex(0);
    REQUIRE(vex != vex1);
}