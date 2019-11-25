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
    Mesh defMesh;
    defMesh.loadFile(std::string("../tests/data/triangulation_files/triangulation#1.tri"));
    REQUIRE(defMesh.getVertices().size() == 1467);
    REQUIRE(defMesh.getVertices().at(0).getAttributes().empty());
    REQUIRE(defMesh.getTriangles().size() == 2620);
    REQUIRE(defMesh.getTriangles().at(0).getAttributes().size() == 17);
}

TEST_CASE("Triangulation file can be populated from mesh", "[mesh]") {
    Mesh defMesh;
    defMesh.loadFile(std::string("../tests/data/triangulation_files/triangulation#4.tri"));
    std::ofstream outfile("../build/triangulation#4_copied.tri", std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open output file.");
    }
    outfile << defMesh;
}