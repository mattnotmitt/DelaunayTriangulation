//
// Created by matt on 17/11/2019.
//
#include <fstream>
#include <string>
#include <catch2/catch.hpp>
#include "../src/utils.hpp"
#include "../src/Triangle.hpp"
#include "../src/Mesh.hpp"

TEST_CASE("Default mesh is constructed", "[mesh][constructor]") {
    Mesh defMesh;
    REQUIRE(defMesh.getVertices().empty());
    REQUIRE(defMesh.getTriangles().empty());
    REQUIRE(defMesh.getVertexAttributes() == 0);
    REQUIRE(defMesh.getTriangleAttributes() == 0);
    REQUIRE(defMesh.getDimensions() == 3);
}

TEST_CASE("Mesh mutator functionality", "[mesh][mutator]") {
   Mesh defMesh;
   std::map<int, Vertex> vert;
   vert[0] = Vertex();
   std::map<int, Triangle> tris;
   tris[0] = Triangle();
   tris[1] = Triangle();
   defMesh.setVertices(vert);
   defMesh.setTriangles(tris);
   defMesh.setVertexAttributes(2);
   defMesh.setTriangleAttributes(3);
    REQUIRE(defMesh.getVertices().size() == 1);
    REQUIRE(defMesh.getTriangles().size() == 2);
    REQUIRE(defMesh.getVertexAttributes() == 2);
    REQUIRE(defMesh.getTriangleAttributes() == 3);
    REQUIRE(defMesh.getDimensions() == 3);
}

TEST_CASE("Mesh is populated from file", "[mesh][input]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#1.tri");
    infile >> defMesh;
    infile.close();
    REQUIRE(defMesh.getVertices().size() == 1467);
    REQUIRE(defMesh.getVertices().at(0).getAttributes().empty());
    REQUIRE(defMesh.getTriangles().size() == 2620);
    REQUIRE(defMesh.getTriangles().at(0).getAttributes().size() == 17);
    REQUIRE(defMesh.getEdges().size() == 4086);
}

TEST_CASE("Triangulation file can be populated from mesh", "[mesh][input][output]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#4.tri");
    infile >> defMesh;
    infile.close();
    std::ofstream outfile;
    Utils::loadFile(outfile, "data/triangulation#4_copied.tri");
    outfile << defMesh;
    outfile.close();
}

TEST_CASE("Node file can be populated from mesh", "[mesh][input][output]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/vertex_files/vertices#1.node");
    infile >> defMesh;
    infile.close();
    std::ofstream outfile;
    Utils::loadFile(outfile, "data/vertices#1_copied.node");
    outfile << defMesh;
    outfile.close();
    REQUIRE(defMesh.getVertices().size() == 22);
    REQUIRE(defMesh.getDimensions() == 2);
    REQUIRE(defMesh.getTriangles().empty());
}

TEST_CASE("Invalid files recognised as such", "[mesh][input][error]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation_bad_prop.tri");
    REQUIRE_THROWS_WITH(infile >> defMesh, "Error on line 1: First non-empty line of file is not a valid declaration.");
    infile.close();
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation_bad_vec.tri");
    REQUIRE_THROWS_WITH(infile >> defMesh, "Error on line 2: Vector declaration has 4 parameters, expecting 6");
    infile.close();
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation_bad_non_tri.tri");
    REQUIRE_THROWS_WITH(infile >> defMesh, "Error on line 6: This program only supports cells consisting of 3 points.");
    infile.close();
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation_bad_cell_prop.tri");
    REQUIRE_THROWS_WITH(infile >> defMesh, "Error on line 5: Invalid cell property line.");
    infile.close();
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation_bad_cell.tri");
    REQUIRE_THROWS_WITH(infile >> defMesh, "Error on line 6: Cell declaration has 5 parameters, expecting 6");
    infile.close();
}

TEST_CASE("Can find owning triangle", "[mesh][eigen][contain]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#2.tri");
    infile >> defMesh;
    infile.close();
    // Inside triangle 12, but inside triangle 0's circumcircle
    REQUIRE(defMesh.containingTriangle(68.125, 0.1) == 12);
    // Circumcentre of triangle 0
    REQUIRE(defMesh.containingTriangle(67.87956, -0.16581) == 0);
}

TEST_CASE("Correct number of adjacent triangles", "[mesh][eigen][triangle]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#1.tri");
    infile >> defMesh;
    infile.close();
    REQUIRE(defMesh.adjacentTriangles(2398).size() == 2);
    REQUIRE(defMesh.adjacentTriangles(101).size() == 3);
}

TEST_CASE("Is Delaunay", "[mesh][delaunay][eigen]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#1.tri");
    infile >> defMesh;
    infile.close();
    REQUIRE(!defMesh.isDelaunay());
    Mesh defMesh1;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#2.tri");
    infile >> defMesh1;
    infile.close();
    REQUIRE(!defMesh1.isDelaunay());
    Mesh defMesh2;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#3.tri");
    infile >> defMesh2;
    infile.close();
    REQUIRE(defMesh2.isDelaunay());
    Mesh defMesh3;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#4.tri");
    infile >> defMesh3;
    infile.close();
    REQUIRE(!defMesh3.isDelaunay());
}

TEST_CASE("Is Delaunay Fails", "[mesh][delaunay][error]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/vertex_files/vertices#1.node");
    infile >> defMesh;
    infile.close();
    REQUIRE_THROWS_WITH(defMesh.isDelaunay(), "Cannot check if mesh is Delaunay Triangulation, no triangles defined.");
}

double func (double x, double y) {return x*3 + y*3;}

TEST_CASE("Integrates", "[mesh][eigen][integration]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#1.tri");
    infile >> defMesh;
    infile.close();
    // Cannot verify how close these are to the real values
    REQUIRE(defMesh.integrate(func, Utils::constantValueApprox) == Approx(3540385.693));
    REQUIRE(defMesh.integrate(func, Utils::linearInterpolationApprox) == Approx(3540385.693));
}