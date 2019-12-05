#include <catch/catch.hpp>
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
    // Vertices excluded as requires valid triangles, is tested in other areas
    Triangle tri;
    std::vector<double> attr(5, 0.99);
    std::vector<int> vert(1, 1);
    tri.setAttributes(attr);
    tri.setIndex(5);
    REQUIRE(tri.getAttributes().size() == 5);
    REQUIRE(tri.getIndex() == 5);
}

TEST_CASE("Circumcircle functionality", "[triangle][mesh][eigen][contain]") {
    Mesh defMesh;
    std::ifstream infile;
    Utils::loadFile(infile, "../tests/data/triangulation_files/triangulation#2.tri");
    infile >> defMesh;
    infile.close();
    Triangle tri = defMesh.getTriangles().at(0);
    // Values computed by wolframalpha: https://www.wolframalpha.com/input/?i=triangle+%7C+vertex+coordinates+%2868.5163%2C+0.00170467%29+%7C+%2867.8335%2C+-0.822605%29+%7C+%2867.2426%2C+0.000876253%29+%7C+circumcircle
    REQUIRE(tri.getCc().x == Approx(67.87956));
    REQUIRE(tri.getCc().y == Approx(-0.16581));
    REQUIRE(tri.getCc().radius == Approx(0.658408));
    Eigen::Vector2d point(68.3,-0.6);
    REQUIRE(tri.circumcircleContainsPoint(point));
}