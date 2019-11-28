//
// Created by matt on 22/11/2019.
//
#include <vector>
#include <Eigen/Dense>
#include "Vertex.hpp"
#include "IMesh.hpp"

#pragma once

class Triangle {
public:
    struct circumcircle {
        double x;
        double y;
        double radius;
    };
private:
    int index;
    circumcircle cc;
    IMesh* owner;
    std::vector<double> attributes;
    std::vector<int> vertices; // int refers to vertex index in mesh
    std::vector<std::pair<int, int> > edges;
public:
    // Constructors
    explicit Triangle() : index(-1), owner() {}
    Triangle(int index, IMesh* owner) : index(index), owner(owner) {};
    // Functionality
    circumcircle calcCircumcircle() const;
    bool circumcircleContainsPoint(const Eigen::Vector2d &p) const;
    bool containsPoint(const Eigen::Vector2d& p) const;
    // Getters & Setters
    int getIndex() const;

    void setIndex(int i);

    const std::vector<int> &getVertices() const;

    void setVertices(const std::vector<int> &vertices);

    const std::vector<double> &getAttributes() const;

    void setAttributes(const std::vector<double> &attributes);

    const circumcircle &getCc() const;

    void setCc(const circumcircle &cc);

    const std::vector<std::pair<int, int> > &getEdges() const;

    void setEdges(const std::vector<std::pair<int, int> > &edges);

    // Stream operators
    friend std::istream &operator>>(std::istream &is, Triangle &triangle);
    friend std::ostream &operator<<(std::ostream &os, Triangle &triangle);
    friend std::ofstream &operator<<(std::ofstream &ofs, Triangle &triangle);

};
