//
// Created by mitt on 01/12/2019.
//

#pragma once
#include <iostream>
#include <fstream>
/**
 * @file Vec.hpp
 * @brief Vec class header
 */

/**
 * Class representing coordinates of a Vector
 * @note Class can only be mutated through recreating vec and setting in parent Vertex class
 */
class Vec {
private:
    double x; ///< x coordinate
    double y; ///< y coordinate
    double z; ///< z coordinate
    int dimensions; ///< number of dimensions in mesh
public:
    /**
     * Default constructor
     */
    Vec() : x(0), y(0), z(0), dimensions(3) {};
    /**
     * Contstructor populating #dimensions
     * @param dim number of dimensions
     */
    explicit Vec(int dim) : x(0), y(0), z(0), dimensions(dim) {};
    /**
     * Constructor populating all members
     * @param x x coordinate
     * @param y y coordinate
     * @param z z coordinate
     * @param dim number of dimensions
     */
    Vec(float x, float y, float z, int dim) : x(x), y(y), z(z), dimensions(dim) {};
    /**
     * Accessor to private member #x
     * @return x coordinate
     */
    double getX() const;
    /**
     * Accessor to private member #y
     * @return y coordinate
     */
    double getY() const;
    /**
     * Accessor to private member #z
     * @return z coordinate
     */
    double getZ() const;
    /**
     * Accessor to private member #dimensions
     * @return number of dimensions
     */
    int getDimensions() const;
    /**
     * Equality operator
     * @param rhs
     * @return
     */
    bool operator==(const Vec &rhs) const;
    /**
     * Non-equality operator
     * @param rhs
     * @return
     */
    bool operator!=(const Vec &rhs) const;
    /**
     * Input stream operator
     * @param is
     * @param vec
     * @return
     */
    friend std::istream &operator>>(std::istream &is, Vec &vec);
    /**
     * Output stream operator
     * @param os
     * @param vec
     * @return
     */
    friend std::ostream &operator<<(std::ostream &os, Vec &vec);
    /**
     * Output filestream operator
     * @param os
     * @param vec
     * @return
     */
    friend std::ofstream &operator<<(std::ofstream &os, Vec &vec);
};
