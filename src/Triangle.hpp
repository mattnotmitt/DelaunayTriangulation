//
// Created by matt on 22/11/2019.
//
#include <vector>
#include "Vertex.hpp"

#pragma once


class Triangle {
private:
    int index;
    std::vector<double> attributes;
    std::vector<int> vertices; // int refers to vertex index in mesh
public:
    explicit Triangle(int index) : index(index), vertices(std::vector<int>()) {};
    friend std::istream &operator>>(std::istream &is, Triangle &triangle);
    friend std::ofstream &operator<<(std::ofstream &os, Triangle &triangle);

    int getIndex() const;

    void setIndex(int i);

    const std::vector<int> &getVertices() const;

    void setVertices(const std::vector<int> &vertices);

    const std::vector<double> &getAttributes() const;

    void setAttributes(const std::vector<double> &attributes);
};
