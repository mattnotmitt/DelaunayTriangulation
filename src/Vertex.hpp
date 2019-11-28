//
// Created by matt on 17/11/2019.
//
#include <vector>
#include <ostream>
#include "IVertex.hpp"
#include "IMesh.hpp"

#pragma once

class Vertex : public IVertex {
private:
    int index;
    int dimensions;
    IMesh* owner;
    float x;
    float y;
    float z;
    std::vector<double> attributes;
public:
    Vertex(int index, int dim, IMesh* owner) : index(index), dimensions(dim), owner(owner), x(0), y(0), z(0),
                                          attributes(std::vector<double>()) {};

    Vertex() : index(-1), dimensions(3), owner(), x(0), y(0), z(0),
               attributes(std::vector<double>()) {};

    // Getters & Setters
    int getIndex() const;

    void setIndex(int index);

    int getDimensions() const;

    void setDimensions(int dimensions);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    const std::vector<double> &getAttributes() const;

    void setAttributes(const std::vector<double> &attributes);

    // Stream Operators
    friend std::istream &operator>>(std::istream &is, Vertex &vertex);
    friend std::ostream &operator<<(std::ostream &os, Vertex &vertex);
    friend std::ofstream &operator<<(std::ofstream &os, Vertex &vertex);
};

