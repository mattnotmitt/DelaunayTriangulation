//
// Created by matt on 17/11/2019.
//

#include <cstdlib>
#include "Vertex.hpp"

int Vertex::getIndex() const {
    return index;
}

void Vertex::setIndex(int index) {
    Vertex::index = index;
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

const std::vector<float> &Vertex::getAttributes() const {
    return attributes;
}

void Vertex::setAttributes(const std::vector<float> &attributes) {
    Vertex::attributes = attributes;
}

std::istream &operator>>(std::istream &is, Vertex &vertex) {
    std::string xs, ys, zs;
    std::vector<float> attributes;
    is >> xs >> ys >> zs;
    vertex.setX((float) std::strtod(xs.c_str(), NULL));
    vertex.setY((float) std::strtod(ys.c_str(), NULL));
    vertex.setZ((float) std::strtod(zs.c_str(), NULL));
    std::string next;
    while (is >> next) {
        attributes.push_back((float) std::strtod(next.c_str(), NULL));
    }
    vertex.setAttributes(attributes);
    return is;
}