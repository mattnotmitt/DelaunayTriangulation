#include <vector>
#include <catch2/catch.hpp>
#include "../src/Vertex.hpp"

TEST_CASE("Default vertex is constructed", "[vertex][constructor]") {
    Vertex vec;
    REQUIRE(vec.getAttributes().empty());
    REQUIRE(vec.getDimensions() == 3);
    REQUIRE(vec.getX() == 0);
    REQUIRE(vec.getY() == 0);
    REQUIRE(vec.getZ() == 0);
    REQUIRE(vec.getIndex() == -1);
}

TEST_CASE("Vertex mutator functionality", "[vertex][mutator]") {
    Vertex vec;
    vec.setIndex(100);
    vec.setDimensions(2);
    vec.setX(1);
    vec.setY(-1);
    vec.setZ(0.01);
    std::vector<double> attr(5, 0.99);
    vec.setAttributes(attr);
    REQUIRE(vec.getAttributes().size() == 5);
    REQUIRE(vec.getDimensions() == 2);
    REQUIRE(vec.getX() == 1);
    REQUIRE(vec.getY() == -1);
    REQUIRE(vec.getZ() == 0.01f);
    REQUIRE(vec.getIndex() == 100);
}
