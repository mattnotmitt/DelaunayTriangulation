//
// Created by matt on 26/11/2019.
//

#pragma once
#include "Vec.hpp"
/**const
 * Shallow class allowing Mesh to be imported in classes which Mesh owns
 */
class IMesh {
public:
    /**
     * Type representing an edge, two vertex indices
     */
    typedef std::pair<int, int> edge;
    /**
     * Virtual destructor
     */
    virtual ~IMesh() {};
    /**
     * Resolves vector of vertex indices to vector of vertex pointers
     * @param pointIndices Vector of indices of vertexes
     * @return Vector of pointers to vertexes matching the indices given by pointIndices
     * @throw std::runtime_error if index is out of range of valid vertices
     */
    virtual std::vector<Vec> resolvePoints(std::vector<int> pointIndices) = 0;
    /**
     * Recalculate the Triangle::circumcircle of all Triangles using vertex represented by vertInd
     * - called after coordinates of a Vertex changed using mutator
     * @param vertInd Index of changed Vector
     */
    virtual void recalcCircum(int vertInd) = 0;
    /**
     * Adds triangle's new edges to map
     * @param triInd index of the triangle using the vertices
     * @param vert Vector of vertex indices being used by the triangle
     * @return Vector of pairs of vectors representing an edge
     */
    virtual std::vector<std::pair<int, int> > newEdges(int triInd, const std::vector<int> &vert) = 0;
    /**
     * Remove triangle's old edges from map
     * @param triInd index of triangle using the vertices
     * @param rEdge Vector of edges that are no longer in use by the triangle
     */
    virtual void removeEdges(int triInd, const std::vector<std::pair<int, int> > &rEdge) = 0;
    /**
     * Add Triangle represented by triInd to vertTri
     * - Used by Mesh::recalcCircum
     * @param triInd Index of triangle to be added
     * @param vertInds Indices of vertices used by Triangle
     */
    virtual void updateVertTri(int triInd, std::vector<int> vertInds) = 0;
    /**
     * Remove triangle index from vertTri
     * @param triInd Index of triangle to be removed
     * @param rVertInds Old indices used by Triangle
     */
    virtual void removeVertTri(int triInd, std::vector<int> rVertInds) = 0;
};

