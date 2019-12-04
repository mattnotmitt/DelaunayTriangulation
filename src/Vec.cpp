//
// Created by mitt on 01/12/2019.
//

#include "Vec.hpp"
#include <iomanip>

double Vec::getX() const {
    return x;
}

double Vec::getY() const {
    return y;
}

double Vec::getZ() const {
    return z;
}

bool Vec::operator==(const Vec &rhs) const {
    return x == rhs.x &&
           y == rhs.y &&
           z == rhs.z;
}

bool Vec::operator!=(const Vec &rhs) const {
    return !(rhs == *this);
}

int Vec::getDimensions() const {
    return dimensions;
}

std::istream &operator>>(std::istream &is, Vec &vec) {
    is >> vec.x >> vec.y;
    if (vec.dimensions == 3) {
        is >> vec.z;
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, Vec &vec) {
    os << std::setprecision(6) << "(" << vec.x << ", " << vec.y;
    if (vec.dimensions == 3) {
        os << std::setprecision(6) << ", " << vec.z;
    }
    os << ")";
    return os;
}

std::ofstream &operator<<(std::ofstream &ofs, Vec &vec) {
    ofs << std::setprecision(6) << vec.x << " " << vec.y;
    if (vec.dimensions == 3) {
        ofs << std::setprecision(6) << " " << vec.z;
    }
    return ofs;
}

