//
// Created by matt on 17/11/2019.
//
#include <vector>
#include <ostream>

#pragma once


class Vertex {
private:
    int index;
    int dimensions;
public:
    int getDimensions() const;

    void setDimensions(int dimensions);

private:
    std::vector<float> coord;
    std::vector<double> attributes;
public:
    explicit Vertex(int index, int dim) : index(index), dimensions(dim), coord(std::vector<float>()), attributes(std::vector<double>()) {};

    Vertex(int index, const std::vector<float> &coord, const std::vector<double> &attr) : index(index), coord(coord),
                                                                                          attributes(attr) {};

    friend std::istream &operator>>(std::istream &is, Vertex &vertex);

    friend std::ofstream &operator<<(std::ofstream &os, Vertex &vertex);

    int getIndex() const;

    void setIndex(int index);

    const std::vector<float> &getCoord() const;

    void setCoord(const std::vector<float> &coord);

    const std::vector<double> &getAttributes() const;

    void setAttributes(const std::vector<double> &attributes);
};

