//
// Created by matt on 22/11/2019.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>
#include <cmath>
#include <stdexcept>
#include <map>
#include "Triangle.hpp"

int Triangle::getIndex() const {
    return index;
}

void Triangle::setIndex(int i) {
    Triangle::index = i;
}

const std::vector<int> &Triangle::getVertices() const {
    return vertices;
}

void Triangle::setVertices(const std::vector<int> &v) {
    if (edges.size() == 3) owner->removeEdges(index, edges);
    if (vertices.size() == 3) owner->removeVertTri(index, vertices);
    if (v.size() != 3) throw std::runtime_error("v must be 3 vertices long.");
    Triangle::vertices = v;
    calcCircumcircle();
    setEdges(owner->newEdges(index, v));
    owner->updateVertTri(index, v);
}

const std::vector<double> &Triangle::getAttributes() const {
    return attributes;
}

void Triangle::setAttributes(const std::vector<double> &a) {
    Triangle::attributes = a;
}

std::istream &operator>>(std::istream &is, Triangle &triangle) {
    std::vector<int> vertices;
    int vertexIndex;
    for (int i = 0; i < 3; i++) {
        is >> vertexIndex;
        vertices.push_back(vertexIndex);
    }
    triangle.setVertices(vertices);
    std::vector<double> attributes;
    double next;
    while (is >> next) {
        attributes.push_back(next);
    }
    triangle.setAttributes(attributes);
    return is;
}

std::ofstream &operator<<(std::ofstream &ofs, Triangle &triangle) {
    ofs << triangle.index << " " << triangle.vertices[0] << " " << triangle.vertices[1] << " "
       << triangle.vertices[2];
    for (int i = 0; i < triangle.attributes.size(); i++) {
        ofs << " " << std::setprecision(12) << triangle.attributes[i];
    }
    ofs << "\n";
    return ofs;
}

void Triangle::calcCircumcircle() {
    std::cout << vertices[0] << std::endl;
    std::vector<IVertex*> resVerts = owner->resolvePoints(vertices);
    std::cout << resVerts[0]->getIndex() << std::endl;
    std::vector<double> centre = std::vector<double>(3);
    Eigen::Matrix3d m;
    m << resVerts[0]->getX(), resVerts[0]->getY(), 1,
            resVerts[1]->getX(), resVerts[1]->getY(), 1,
            resVerts[2]->getX(), resVerts[2]->getY(), 1;
    Eigen::Vector3d v(pow(resVerts[0]->getX(), 2) + pow(resVerts[0]->getY(), 2),
                      pow(resVerts[1]->getX(), 2) + pow(resVerts[1]->getY(), 2),
                      pow(resVerts[2]->getX(), 2) + pow(resVerts[2]->getY(), 2)
    );
    Eigen::Vector3d res = m.colPivHouseholderQr().solve(v);
    Triangle::circumcircle circc = {};
    circc.x = res(0) / 2.;
    circc.y = res(1) / 2.;
    circc.radius = std::sqrt(res(2) + std::pow(circc.x, 2) + std::pow(circc.y, 2));
    setCc(circc);
}

bool Triangle::circumcircleContainsPoint(const Eigen::Vector2d &p) const {
    Eigen::Vector2d c(cc.x, cc.y);
    double dist = abs((p - c).norm());
    return (float) dist < (float) cc.radius;
}

/**
 * @details Given a point @f$r = \left(\begin{matrix}x \\ y\end{matrix}\right)@f$ and a Triangle made up of points @f$r_1, r_2, r_3@f$ where @f$r_i = \left(\begin{matrix}x_i\\ y_i\end{matrix}\right)@f$, the barycentric coordinates of p, @f$(\lambda_1, \lambda_2, \lambda_3)@f$ can be determined
@f[
\left(\begin{matrix}\lambda_1 \\ \lambda_2\end{matrix}\right) = \left(\begin{matrix}
x_1-x_3 & x_2-x_3 \\
y_1-y_3 & y_2-y_3 \\
\end{matrix}\right)^{-1} \left( \left(\begin{matrix}x \\ y\end{matrix}\right)-\left(\begin{matrix}x_3\\ y_3\end{matrix}\right) \right)
@f]
@f[
	\lambda_3 = 1 - \lambda_1 - \lambda_2
@f]
 */

Eigen::Vector3d Triangle::barycentric(const Eigen::Vector2d &p) const {
    // Barycentric Technique https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    std::vector<IVertex*> resVerts = owner->resolvePoints(vertices);
    Eigen::Matrix2d T;
    T << resVerts[0]->getX() - resVerts[2]->getX(), resVerts[1]->getX() - resVerts[2]->getX(),
            resVerts[0]->getY() - resVerts[2]->getY(), resVerts[1]->getY() - resVerts[2]->getY();
    Eigen::Vector2d r3(resVerts[2]->getX(), resVerts[2]->getY());
    Eigen::Vector2d res = T.inverse() * (p - r3);
    return Eigen::Vector3d(res(0), res(1), 1 - res(0) - res(1));
}

bool Triangle::containsPoint(const Eigen::Vector2d &p) const {
    if (!circumcircleContainsPoint(p)) return false; // If not in circumcircle, definitely not in triangle, save computationally expensive vector maths
    Eigen::Vector3d bar = barycentric(p);
    return (bar(0) >= 0) && (bar(1) >= 0) && (bar(2) >= 0);
}

const Triangle::circumcircle &Triangle::getCc() const {
    return cc;
}

void Triangle::setCc(const Triangle::circumcircle &cc) {
    Triangle::cc = cc;
}

const std::vector<std::pair<int, int> > &Triangle::getEdges() const {
    return edges;
}

void Triangle::setEdges(const std::vector<std::pair<int, int> > &es) {
    Triangle::edges = es;
}

bool Triangle::operator==(const Triangle &rhs) const {
    return index == rhs.index &&
           owner == rhs.owner &&
           attributes == rhs.attributes &&
           vertices == rhs.vertices &&
           edges == rhs.edges;
}

bool Triangle::operator!=(const Triangle &rhs) const {
    return !(rhs == *this);
}
