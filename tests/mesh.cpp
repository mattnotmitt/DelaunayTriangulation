//
// Created by matt on 17/11/2019.
//
#include <string>
#include "tests.hpp"
#include "../src/Mesh.hpp"

TEST_CASE("Mesh is constructed", "[mesh]") {
    Mesh defMesh = Mesh();
    REQUIRE(defMesh.getVertices().empty());
}

TEST_CASE("Mesh is populated from file", "[mesh]") {
    Mesh defMesh = Mesh();
    defMesh.loadFile(std::string("../tests/data/triangulation_files/triangulation#1.tri"));
    REQUIRE(defMesh.getVertices().size() == 1467);
    REQUIRE(defMesh.getVertices().at(0).getAttributes().size() == 0);
    REQUIRE(defMesh.getTriangles().size() == 2620);
    REQUIRE(defMesh.getTriangles().at(0).getAttributes().size() == 17);
}