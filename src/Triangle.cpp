//
// Created by matt on 22/11/2019.
//

#include <cstdlib>
#include <iostream>
#include "Triangle.hpp"

std::istream &operator>>(std::istream &is, Triangle &triangle) {
    std::vector<int> vertices;
    for (int i = 0; i < 3; i++) {
        std::string vertexIndex;
        is >> vertexIndex;
        vertices.push_back((int) std::strtol(vertexIndex.c_str(), NULL, 10));
    }
    triangle.setVertices(vertices);
    std::vector<float> attributes;
    std::string next;
    while (is >> next) {
        attributes.push_back((float) std::strtod(next.c_str(), NULL));
    }
    triangle.setAttributes(attributes);
    return is;
}

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

const std::vector<float> &Triangle::getAttributes() const {
    return attributes;
}

void Triangle::setAttributes(const std::vector<float> &a) {
    Triangle::attributes = a;
}

