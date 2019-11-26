//
// Created by matt on 17/11/2019.
//

#include <map>
#include <memory>
#include <ostream>
#include "Vertex.hpp"
#include "Triangle.hpp"
#include "IMesh.hpp"

#pragma once


class Mesh : public IMesh {
private:
    int vertexAttributes;
    int triangleAttributes;
    int dimensions;
    std::map<int, Vertex> vertices;
    std::map<int, Triangle> triangles;
public:
    // Constructors
    Mesh() : vertexAttributes(0), triangleAttributes(0), dimensions(3) {};
    // Functionality
    std::vector<Vertex> resolvePoints(std::vector<int> pointIndices);
    int containingTriangle(float x, float y);
    // Getters & Setters
    const std::map<int, Vertex> &getVertices() const;

    void setVertices(const std::map<int, Vertex> &vertices);

    const std::map<int, Triangle> &getTriangles() const;

    void setTriangles(const std::map<int, Triangle> &triangles);

    int getVertexAttributes() const;

    void setVertexAttributes(int verAttr);

    int getTriangleAttributes() const;

    void setTriangleAttributes(int triAttr);

    int getDimensions() const;

    void setDimensions(int dimensions);

    // Stream Operators
    friend std::ifstream &operator>>(std::ifstream &ifs, Mesh &mesh);

    friend std::ofstream &operator<<(std::ofstream &ofs, Mesh &mesh);
};
