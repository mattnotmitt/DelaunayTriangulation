#include <vector>
#include <catch2/catch.hpp>
#include "../src/Vertex.hpp"

TEST_CASE("Default vertex is constructed", "[vertex][constructor]") {
    Vertex vec;
    REQUIRE(vec.getAttributes().empty());
    REQUIRE(vec.getX() == 0);
    REQUIRE(vec.getY() == 0);
    REQUIRE(vec.getZ() == 0);
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
