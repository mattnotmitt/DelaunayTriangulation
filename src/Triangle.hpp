//
// Created by matt on 22/11/2019.
//
#include <vector>
#include "Vertex.hpp"
#include "IMesh.hpp"

#pragma once

class Triangle {
private:
    int index;
    IMesh* owner;
    std::vector<double> attributes;
    std::vector<int> vertices; // int refers to vertex index in mesh
public:
    // Constructors
    explicit Triangle() : index(-1), owner() {}
    Triangle(int index, IMesh* owner) : index(index), owner(owner) {};
    // Functionality
    std::vector<float> circumcirle();

    // Getters & Setters
    int getIndex() const;

    void setIndex(int i);

    const std::vector<int> &getVertices() const;

    void setVertices(const std::vector<int> &vertices);

    const std::vector<double> &getAttributes() const;

    void setAttributes(const std::vector<double> &attributes);

    // Stream operators
    friend std::istream &operator>>(std::istream &is, Triangle &triangle);

    friend std::ofstream &operator<<(std::ofstream &os, Triangle &triangle);
};
