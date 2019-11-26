//
// Created by matt on 17/11/2019.
//

#include <ostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "Vertex.hpp"

int Vertex::getIndex() const {
    return index;
}

void Vertex::setIndex(int ind) {
    Vertex::index = ind;
}

int Vertex::getDimensions() const {
    return dimensions;
}

void Vertex::setDimensions(int dimensions) {
    Vertex::dimensions = dimensions;
}


float Vertex::getX() const {
    return x;
}

void Vertex::setX(float x) {
    Vertex::x = x;
}

float Vertex::getY() const {
    return y;
}

void Vertex::setY(float y) {
    Vertex::y = y;
}

float Vertex::getZ() const {
    return z;
}

void Vertex::setZ(float z) {
    Vertex::z = z;
}

const std::vector<double> &Vertex::getAttributes() const {
    return attributes;
}

void Vertex::setAttributes(const std::vector<double> &attr) {
    Vertex::attributes = attr;
}

std::istream &operator>>(std::istream &is, Vertex &vertex) {
    std::vector<double> attributes;
    is >> vertex.x >> vertex.y;
    if (vertex.dimensions == 3) {
        is >> vertex.z;
    }
    double nextAt;
    while (is >> nextAt) {
        attributes.push_back(nextAt);
    }
    vertex.setAttributes(attributes);
    return is;
}

std::ofstream &operator<<(std::ofstream &os, Vertex &vertex) {
    os << vertex.index << std::setprecision(6) << " " << vertex.x << " " << vertex.y;
    if (vertex.dimensions == 3) {
        os << std::setprecision(6) << " " << vertex.z;
    }
    for (int i = 0; i < vertex.attributes.size(); i++) {
        os << std::setprecision(12) << " "  << vertex.attributes[i];
    }
    os << "\n";
    return os;
}
