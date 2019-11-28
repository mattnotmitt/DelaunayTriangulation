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
    if (v.size() != 3) throw std::runtime_error("Cannot set triangle vertices to a ");
    Triangle::vertices = v;
    Triangle::cc = calcCircumcircle();
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

Triangle::circumcircle Triangle::calcCircumcircle() const {
    std::vector<IVertex*> resVerts = owner->resolvePoints(vertices);
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
    Triangle::circumcircle cc = {};
    cc.x = res(0) / 2.;
    cc.y = res(1) / 2.;
    cc.radius = sqrt(res(2) + pow(cc.x, 2) + pow(cc.y, 2));
    return cc;
}

bool Triangle::circumcircleContainsPoint(const Eigen::Vector2d &p) const {
    Eigen::Vector2d c(cc.x, cc.y);
    double dist = abs((p - c).norm());
    return (float) dist < (float) cc.radius;
}
/**
 * Checks whether
 * @param p
 * @return boolean - whether the triangle contains p
 */
bool Triangle::containsPoint(const Eigen::Vector2d &p) const {
    if (!circumcircleContainsPoint(p)) return false; // If not in circumcircle, definitely not in triangle, save computationally expensive vector maths
    // Barycentric Technique https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Conversion_between_barycentric_and_Cartesian_coordinates
    std::vector<IVertex*> resVerts = owner->resolvePoints(vertices);
    Eigen::Matrix2d T;
    T << resVerts[0]->getX() - resVerts[2]->getX(), resVerts[1]->getX() - resVerts[2]->getX(),
            resVerts[0]->getY() - resVerts[2]->getY(), resVerts[1]->getY() - resVerts[2]->getY();
    Eigen::Vector2d r3(resVerts[2]->getX(), resVerts[2]->getY());
    Eigen::Vector2d res = T.inverse() * (p - r3);
    return (res(0) >= 0) && (res(1) >= 0) && (res(0) + res(1) < 1);
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
