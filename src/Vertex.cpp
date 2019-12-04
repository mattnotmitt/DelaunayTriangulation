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

const std::vector<double> &Vertex::getAttributes() const {
    return attributes;
}

void Vertex::setAttributes(const std::vector<double> &attr) {
    Vertex::attributes = attr;
}

std::istream &operator>>(std::istream &is, Vertex &vertex) {
    std::vector<double> attributes;
    is >> vertex.vec;
    double nextAt;
    while (is >> nextAt) {
        attributes.push_back(nextAt);
    }
    vertex.setAttributes(attributes);
    return is;
}

std::ostream &operator<<(std::ostream &os, Vertex &vertex) {
    os << vertex.vec;
    return os;
}

std::ofstream &operator<<(std::ofstream &ofs, Vertex &vertex) {
    ofs << vertex.index << " ";
    ofs << vertex.vec;
    for (int i = 0; i < vertex.attributes.size(); i++) {
        ofs << std::setprecision(12) << " "  << vertex.attributes[i];
    }
    ofs << "\n";
    return ofs;
}

bool Vertex::operator==(const Vertex &rhs) const {
    return index == rhs.index &&
           owner == rhs.owner &&
           vec == vec &&
           attributes == rhs.attributes;
}

bool Vertex::operator!=(const Vertex &rhs) const {
    return !(rhs == *this);
}

const Vec &Vertex::getVec() const {
    return vec;
}

void Vertex::setVec(const Vec &vec) {
    Vertex::vec = vec;
    owner->recalcCircum(index);
}
