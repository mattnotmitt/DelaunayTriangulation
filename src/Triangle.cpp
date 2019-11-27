//
// Created by matt on 22/11/2019.
//

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>
#include <math.h>
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
    Triangle::vertices = v;
}

const std::vector<double> &Triangle::getAttributes() const {
    return attributes;
}

void Triangle::setAttributes(const std::vector<double> &a) {
    Triangle::attributes = a;
}

std::istream &operator>>(std::istream &is, Triangle &triangle) {
    std::vector<int> vertices;
    for (int i = 0; i < 3; i++) {
        std::string vertexIndex;
        is >> vertexIndex;
        vertices.push_back((int) std::strtol(vertexIndex.c_str(), NULL, 10));
    }
    triangle.setVertices(vertices);
    std::vector<double> attributes;
    std::string next;
    while (is >> next) {
        attributes.push_back(std::strtod(next.c_str(), NULL));
    }
    triangle.setAttributes(attributes);
    return is;
}

std::ofstream &operator<<(std::ofstream &os, Triangle &triangle) {
    std::stringstream ss;
    ss << std::setprecision(6) << triangle.index << " " << triangle.vertices[0] << " " << triangle.vertices[1] << " " << triangle.vertices[2];
    for (int i = 0; i < triangle.attributes.size(); i++) {
        ss << " " << std::setprecision(12) << triangle.attributes[i];
    }
    os << ss.str().c_str() << "\n";
    return os;
}

std::vector<float> Triangle::circumcirle() const {
    std::vector<Vertex> resVerts = owner->resolvePoints(vertices);
    Eigen::Matrix3f m;
    m << resVerts[0].getX(), resVerts[0].getY(), 1,
        resVerts[1].getX(), resVerts[1].getY(), 1,
        resVerts[2].getX(), resVerts[2].getY(), 1;
    Eigen::Vector3f v(pow(resVerts[0].getX(), 2) + pow(resVerts[0].getY(), 2),
                      pow(resVerts[1].getX(), 2) + pow(resVerts[1].getY(), 2),
                      pow(resVerts[2].getX(), 2) + pow(resVerts[2].getY(), 2)
            );
    Eigen::Vector3f res = m.colPivHouseholderQr().solve(v);
    return std::vector<float>();
}
