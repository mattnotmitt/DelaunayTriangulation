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
/**
 * @file Mesh.hpp
 * @brief Mesh class header
 */
// Whole program could (?) be sped up using DCEL https://en.wikipedia.org/wiki/Doubly_connected_edge_list
/**
 * Parent class of all objects, contains full triangulation and its constituent parts
 */
class Mesh : public IMesh {
private:
    int vertexAttributes; /**< Number of attributes in a vertex object */
    int triangleAttributes; /**< Number of attributes in a triangle object */
    int dimensions; /**< Number of dimensions of the mesh */
    std::map<int, Triangle> triangles; /**< Map of triangle indices to triangles they refer to */
    std::map<int, Vertex> vertices; /**< Map of vertex indices to vertices they refer to */

    /**
     * Map of pairs of vertex indices (representing an edge) to a vector of triangles using them
     *  - Used to find adjacent triangles
     */
    std::map<edge, std::vector<int> > edges;
    /**
     * Map of a vertex index to a vector of triangles using them
     * - Used to find circumcentres that must be updated when vector values change
     */
    std::map<int, std::vector<int> > vertTri;
public:
    // Constructors
    /**
     * Default contructor
     */
    Mesh() : vertexAttributes(0), triangleAttributes(0), dimensions(3) {};
    /**
     * Default destructor
     */
    ~Mesh() {};
    // Functionality
    /**
     * Implementation of IMesh::resolvePoints
     * Resolves vector of vertex indices to vector of vertex pointers
     * @param vertInds Vector of indices of vertexes
     * @return Vector of coordinates matching the indices given by pointIndices
     * @throw std::runtime_error if index is out of range of valid vertices
     */
    std::vector<Vec> resolvePoints(std::vector<int> vertInds);
    /**
     * Checks whether mesh is Delauney
     * @return bool representing whether or not mesh is Delauney
     * @throw std::runtime_error if mesh has no triangles
     */
    bool isDelaunay();
    /**
     * Implementation of IMesh::newEdges
     * Adds triangle's new edges to map
     * @param triInd index of the triangle using the vertices
     * @param vert Vector of vertex indices being used by the triangle
     * @return Vector of pairs of vectors representing an edge
     */
    std::vector<edge> newEdges(int triInd, const std::vector<int> &vert);
    /**
     * Implementation of IMesh::removeEdges
     * Remove triangle's old edges from map
     * @param triInd index of triangle using the vertices
     * @param rEdge Vector of edges that are no longer in use by the triangle
     */
    void removeEdges(int triInd, const std::vector<std::pair<int, int> > &rEdge);
    /**
     * Find the triangle which contains the point @f$(x,y)@f$
     * @param x
     * @param y
     * @return Index of containing triangle, or -1 if not inside
     */
    int containingTriangle(double x, double y);
    /**
     * Find all triangles that share an edge with triangle represented by triInd
     * @param triInd Index of querying triangle
     * @return Vector of indices of adjacent triangles
     */
    std::vector<int> adjacentTriangles(int triInd);
    /**
     * Implementation of IMesh::recalcCircum
     * Recalculate the Triangle::circumcircle of all Triangles using vertex represented by vertInd
     * - called after coordinates of a Vertex changed using mutator
     * @param vertInd Index of changed Vector
     */
    void recalcCircum(int vertInd);
    /**
     * Implementation of IMesh::updateVertTri
     * Add Triangle represented by triInd to vertTri
     * - Used by Mesh::recalcCircum
     * @param triInd Index of triangle to be added
     * @param vertInds Indices of vertices used by Triangle
     */
    void updateVertTri(int triInd, std::vector<int> vertInds);
    /**
     * Implementation of IMesh::removeVertTri
     * Remove triangle index from vertTri
     * @param triInd Index of triangle to be removed
     * @param rVertInds Old indices used by Triangle
     */
    void removeVertTri(int triInd, std::vector<int> rVertInds);
    /**
     * Estimate the integral of the function func over the mesh
     * @tparam T function with signature double (double, double)
     * @param func Mathematical function to be integrated
     * @param interp Function with signature double(T, const Triangle&) which will integrate the function over a triangle
     *  Examples are Utils::constantValueApprox and Utils::linearInterpolationApprox
     * @return Estimation of the integral
     */
    template <typename T>
    double integrate(T func, double (*interp)(T, const Triangle&)) {
        double res = 0;
        for (int i = 0; i < triangles.size(); i++) {
            res += std::abs(interp(func, triangles[i]));
        }
        return res;
    };
    // Getters & Setters
    /**
     * Accessor to private member #vertices
     * @return Map of indices to Vertex instances
     */
    const std::map<int, Vertex> &getVertices() const;
    /**
     * Mutator for private member #vertices
     * @param vertices Map of indices to Vertex instances
     */
    void setVertices(const std::map<int, Vertex> &vertices);
    /**
     * Accessor to private member #vertices
     * @return Map of indices to Triangle instances
     */
    const std::map<int, Triangle> &getTriangles() const;
    /**
     * Mutator for private member #triangles
     * @param triangles Map of indices to Triangle instances
     */
    void setTriangles(const std::map<int, Triangle> &triangles);
    /**
     * Accessor for private member #vertexAttributes
     * @return number of Vertex attributes
     */
    int getVertexAttributes() const;
    /**
     * Mutator for private member #vertexAttributes
     * @param verAttr number of Vertex attributes
     */
    void setVertexAttributes(int verAttr);
    /**
     * Accessor for private member #triangleAttributes
     * @return number of Triangle attributes
     */
    int getTriangleAttributes() const;
    /**
     * Mutator for private member #triangleAttributes
     * @param triAttr number of Triangle attributes
     */
    void setTriangleAttributes(int triAttr);
    /**
     * Accessor for private member #dimensions
     * @return number of dimensions
     */
    int getDimensions() const;
    /**
     * Accessor for private member #edges
     * @return Map of pairs of vertex indices (edges) to a std::vector of triangle indices that use that side
     */
    const std::map<std::pair<int, int>, std::vector<int> > &getEdges() const;
    // Equality Operators
    /// \note Copy operator is generated by the compiler
    /**
     * Equality operator
     * @param rhs
     * @return
     */
    bool operator==(const Mesh &rhs) const;
    /**
     * Not-equality operator
     * @param rhs
     * @return
     */
    bool operator!=(const Mesh &rhs) const;
    // Stream Operators
    /**
     * Input filestream operator
     * @param ifs
     * @param mesh
     * @return
     */
    friend std::ifstream &operator>>(std::ifstream &ifs, Mesh &mesh);
    /**
     * Output filestream operator
     * @param ofs
     * @param mesh
     * @return
     */
    friend std::ofstream &operator<<(std::ofstream &ofs, Mesh &mesh);
};
