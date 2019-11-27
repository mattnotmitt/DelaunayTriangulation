#include <catch2/catch.hpp>
#include <fstream>
#include "../src/utils.hpp"
#include "../src/Triangle.hpp"
#include "../src/Vertex.hpp"
#include "../src/Mesh.hpp"

TEST_CASE("Default triangle is constructed", "[triangle][constructor]") {
    Triangle tri;
    REQUIRE(tri.getAttributes().empty());
    REQUIRE(tri.getVertices().empty());
    REQUIRE(tri.getIndex() == -1);
}

TEST_CASE("Triangle mutator functionality", "[triangle][mutator]") {
    Triangle tri;
    std::vector<double> attr(5, 0.99);
    std::vector<int> vert(1, 1);
    tri.setAttributes(attr);
    tri.setVertices(vert);
    tri.setIndex(5);
    REQUIRE(tri.getAttributes().size() == 5);
    REQUIRE(tri.getVertices().size() == 1);
    REQUIRE(tri.getIndex() == 5);
}

TEST_CASE("Circumcircle functionality", "[triangle][mesh][eigen]") {
    Mesh defMesh;
    std::ifstream infile;
    utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#2.tri");
    infile >> defMesh;
    infile.close();
    defMesh.getTriangles().at(0).circumcirle();
}