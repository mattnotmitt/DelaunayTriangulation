//
// Created by matt on 22/11/2019.
//
#include <vector>
#include <Eigen/Dense>
#include "IMesh.hpp"

#pragma once
/**
 * @file Triangle.hpp
 * @brief Triangle class header
 */

/**
 * Class representing a polygon with 3 points and its member functions
 */
class Triangle {
public:
    /**
     * Circumcircle object
     */
    struct circumcircle {
        /**
         * x coordinate of the circumcentre
         */
        double x;
        /**
         * y coordinate of the circumcentre
         */
        double y;
        /**
         * radius of the circumcircle
         */
        double radius;
    };
private:
    int index; ///< Index of the triangle (loaded from file)
    circumcircle cc; ///< Circumcircle of the current triangle
    IMesh *owner; ///< Pointer to interface class of the Mesh the Triangle is part of
    std::vector<double> attributes; ///< Vector of attributes of the Triangle (16 points of precision)
    std::vector<int> vertices; ///< Vector of vertex indices making up the Triangle
    std::vector<IMesh::edge> edges; ///< Vector of edges making up the Triangle
public:
    // Constructors
    /**
     * Default constructor
     */
    Triangle() : index(-1), owner(), cc() {}
    /**
     * Constructor populating #index and #owner
     * @param index Index of Triangle according to file
     * @param owner Pointer to Mesh the Triangle is a part of
     */
    Triangle(int index, IMesh *owner) : index(index), owner(owner), cc() {};
    /**
     * Default destructor
     */
    ~Triangle() {};
    // Functionality
    /**
     * Calculate the circumcircle of the Triangle
     */
    void calcCircumcircle();
    /**
     * Check if the circumcircle of the Triangle contains a point
     * @param p 2 element double-precision Eigen3 vector storing the point
     * @return Whether the circumcircle contains the point
     */
    bool circumcircleContainsPoint(const Eigen::Vector2d &p) const;
    /**
     * Get the barycentric coordinates of a point in relation to the triangle
     * @param p 2 element double-precision Eigen3 vector storing the point in cartesian coordinates
     * @return 3 element double-precision Eigen3 vector storing the poit in barycentric coordinates
     */
    Eigen::Vector3d barycentric(const Eigen::Vector2d &p) const;
    /**
     * Check if the Triangle contains a point
     * @param p 2 element double-precision Eigen3 vector storing the point
     * @return Whether the triangle contains the point
     */
    bool containsPoint(const Eigen::Vector2d &p) const;
    /**
     * Calculate the area of the triangle in 2d (x & y coords)
     * @return area of triangle
     */
    double area() const;
    // Getters & Setters
    /**
     * Accessor for private member #index
     * @return index of Triangle or -1 if not part of mesh
     */
    int getIndex() const;
    /**
     * Mutator for private member #index
     * @param i index of Triangle
     */
    void setIndex(int i);
    /**
     * Accessor for private member #vertices
     * @return vector of vertex indices
     */
    const std::vector<int> &getVertices() const;
    /**
     * Mutator for private member #vertices
     * @param vertices vector of vertex indices
     */
    void setVertices(const std::vector<int> &vertices);
    /**
     * Accessor for private member #attributes
     * @return vector of triangle attributes
     */
    const std::vector<double> &getAttributes() const;
    /**
     * Mutator for private member #attributes
     * @param attributes vector of triangle attributes
     */
    void setAttributes(const std::vector<double> &attributes);
    /**
     * Accessor for private member #cc
     * @return struct describing the circumcircle of the triangle
     */
    const circumcircle &getCc() const;
    /**
     * Mutator for private member #cc
     * @param cc struct describing the circumcircle of the triangle
     */
    void setCc(const circumcircle &cc);
    /**
     * Accessor for private member #edges
     * @return vector of edges making up the triangle
     */
    const std::vector<IMesh::edge> &getEdges() const;
    /**
     * Mutator for private member #edges
     * @param edges vector of edges making up the triangle
     */
    void setEdges(const std::vector<IMesh::edge> &edges);
    /**
     * Accessor for private member #owner
     * @return pointer to owning Mesh interface class
     */
    IMesh *getOwner() const;
    // Comparison Operators
    /**
     * Equality operator
     * @param rhs
     * @return
     */
    bool operator==(const Triangle &rhs) const;
    /**
     * Non-equality operator
     * @param rhs
     * @return
     */
    bool operator!=(const Triangle &rhs) const;

    // Stream operators
    /**
     * Input stream operator
     * @param is
     * @param triangle
     * @return
     */
    friend std::istream &operator>>(std::istream &is, Triangle &triangle);
    /**
     * Output stream operator
     * @param os
     * @param triangle
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, Triangle &triangle);
    /**
     * Output filestream operator
     * @param ofs
     * @param triangle
     * @return
     */
    friend std::ofstream &operator<<(std::ofstream &ofs, Triangle &triangle);
};
