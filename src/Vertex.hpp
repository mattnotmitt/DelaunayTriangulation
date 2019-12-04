//
// Created by matt on 17/11/2019.
//
#include <vector>
#include <ostream>
#include "IMesh.hpp"
#include "Vec.hpp"

#pragma once
/**
 * @file Vertex.hpp
 * @brief Vertex class header
 */
/**
 * Class representing a vertex of a cell
 */
class Vertex {
private:
    int index; ///< Index of the triangle from file
    IMesh* owner; ///< Pointer to interface class of the Mesh the Vertex is a part of
    Vec vec; ///< Vec class storing the coordinates of the vertex
    std::vector<double> attributes; ///< Vector of attributes of the Vertex (16 points of precision)
public:
    /**
     * Constructor populating #index and #owner and instantiating #vec
     * @param index Index of vertex according to file
     * @param dim Dimensions in the mesh - passed to Vec
     * @param owner Pointer to Mesh the Vertex is a part of
     */
    Vertex(int index, int dim, IMesh* owner) : index(index), owner(owner), vec(0, 0, 0, dim) {};
    /**
     * Default constructor
     */
    Vertex() : index(-1), owner(), vec(0, 0, 0, 3) {};
    /**
     * Default destructor
     */
    ~Vertex() {};
    // Getters & Setters
    /**
     * Accessor for private member #index
     * @return index of vertex or -1 if not part of mesh
     */
    int getIndex() const;
    /**
     * Mutator for private member #index
     * @param index index of vertex
     */
    void setIndex(int index);
    /**
     * Accessor for private member #attributes
     * @return vector of vertex attributes
     */
    const std::vector<double> &getAttributes() const;
    /**
     * Mutator for private member #attributes
     * @param attributes vector of vertex attributes
     */
    void setAttributes(const std::vector<double> &attributes);
    /**
     * Accessor for private member #vec
     * @return Vec object of vertex
     */
    const Vec &getVec() const;
    /**
     * Mutator for private member #vec
     * @param vec Vec object
     */
    void setVec(const Vec &vec);

    // Comparison Operators
    /**
     * Equality operator
     * @param rhs
     * @return
     */
    bool operator==(const Vertex &rhs) const;
    /**
     * Non-equality operator
     * @param rhs
     * @return
     */
    bool operator!=(const Vertex &rhs) const;

    // Stream Operators
    /**
     * Input stream operator
     * @param is
     * @param vertex
     * @return
     */
    friend std::istream &operator>>(std::istream &is, Vertex &vertex);
    /**
     * Output stream operator
     * @param os
     * @param vertex
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, Vertex &vertex);
    /**
     * Output filestream operator
     * @param ofs
     * @param vertex
     * @return
     */
    friend std::ofstream &operator<<(std::ofstream &ofs, Vertex &vertex);
};

