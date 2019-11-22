//
// Created by matt on 17/11/2019.
//

#include <map>
#include <memory>
#include <ostream>
#include "Vertex.hpp"
#include "Triangle.hpp"

#pragma once


class Mesh {
private:
    std::map<int, Vertex> vertices;
    std::map<int, Triangle> triangles;
public:
    Mesh() : vertices(std::map<int, Vertex>()), triangles(std::map<int,Triangle>()) {};

    void loadFile(const std::string &filePath);
    const std::map<int, Vertex> &getVertices() const;
    void setVertices(const std::map<int, Vertex> &vertices);
    const std::map<int, Triangle> &getTriangles() const;
    void setTriangles(const std::map<int, Triangle> &triangles);

    friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh);
};
