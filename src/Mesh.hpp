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

// Whole program could be sped up using DCEL https://en.wikipedia.org/wiki/Doubly_connected_edge_list
class Mesh : public IMesh {
public:
    typedef std::pair<int, int> vectPair;
private:
    int vertexAttributes;
    int triangleAttributes;
    int dimensions;
    std::map<int, Vertex> vertices;
    std::map<int, Triangle> triangles;
    //! Map of pairs of vertices to a vector of triangles using them - used to find adjacent triangles
    std::map<std::pair<int,int>, std::vector<int> > edges;
    //! Map of vertices to a vector of triangles using them - used to find circumcentres that must be updated when vector values change
    std::map<int, std::vector<int> > vertTri;
public:
    // Constructors
    Mesh() : vertexAttributes(0), triangleAttributes(0), dimensions(3) {};
    // Functionality
    std::vector<IVertex*> resolvePoints(std::vector<int> pointIndices);
    bool isDelaunay();
    std::vector<std::pair<int, int> > newEdges(int triInd, const std::vector<int> &vert);
    void removeEdges(int triInd, const std::vector<std::pair<int, int> > &rEdge);
    int containingTriangle(float x, float y);
    std::vector<int> adjacentTriangles(int triInd);
    void recalcCircum(int pointInd);
    void updateVertTri(int triInd, std::vector<int> vertInds);
    void removeVertTri(int triInd, std::vector<int> rVertInds);
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

    const std::map<std::pair<int, int>, std::vector<int> > &getEdges() const;

    void setEdges(const std::map<std::pair<int, int>, std::vector<int> > &edges);

    const std::map<int, std::vector<int> > &getVertTri() const;

    void setVertTri(const std::map<int, std::vector<int> > &vertTri);

    // Stream Operators
    friend std::ifstream &operator>>(std::ifstream &ifs, Mesh &mesh);

    friend std::ofstream &operator<<(std::ofstream &ofs, Mesh &mesh);
};
