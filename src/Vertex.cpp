//
// Created by matt on 17/11/2019.
//

#include <cstdlib>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "Vertex.hpp"

int Vertex::getIndex() const {
    return index;
}

void Vertex::setIndex(int index) {
    Vertex::index = index;
}

const std::vector<double> &Vertex::getAttributes() const {
    return attributes;
}

void Vertex::setAttributes(const std::vector<double> &attributes) {
    Vertex::attributes = attributes;
}

std::istream &operator>>(std::istream &is, Vertex &vertex) {
    std::vector<float> coord;
    std::vector<double> attributes;
    std::string nextCo;
    for (int i = 0; i < vertex.dimensions; i++) {
        is >> nextCo;
        coord.push_back(std::strtod(nextCo.c_str(), NULL));
    }
    vertex.setCoord(coord);
    std::string nextAt;
    while (is >> nextAt) {
        attributes.push_back(std::strtod(nextAt.c_str(), NULL));
    }
    vertex.setAttributes(attributes);
    return is;
}

std::ofstream &operator<<(std::ofstream &os, Vertex &vertex) {
    std::stringstream ss;
    ss << vertex.index;
    for (int i = 0; i < vertex.dimensions; i++) {
        ss << std::setprecision(6) << " " << vertex.coord[i];
    }
    for (int i = 0; i < vertex.attributes.size(); i++) {
        ss << std::setprecision(12) << " "  << vertex.attributes[i];
    }
    os << ss.str().c_str() << "\n";
    return os;
}

const std::vector<float> &Vertex::getCoord() const {
    return coord;
}

void Vertex::setCoord(const std::vector<float> &coord) {
    Vertex::coord = coord;
}

int Vertex::getDimensions() const {
    return dimensions;
}

void Vertex::setDimensions(int dimensions) {
    Vertex::dimensions = dimensions;
}
