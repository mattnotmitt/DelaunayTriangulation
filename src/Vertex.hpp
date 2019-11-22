//
// Created by matt on 17/11/2019.
//
#include <vector>
#include <ostream>

#pragma once


class Vertex {
private:
    int index;
    float x;
    float y;
    float z;
    std::vector<float> attributes;
public:
    explicit Vertex(int index) : index(index), x(0), y(0), z(0), attributes(std::vector<float>()) {};
    Vertex(int index, float x, float y, float z, const std::vector<float>& attr) : index(index), x(x), y(y), z(z), attributes(attr) {};

    friend std::istream &operator>>(std::istream &is, Vertex &vertex);

    int getIndex() const;

    void setIndex(int index);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    const std::vector<float> &getAttributes() const;

    void setAttributes(const std::vector<float> &attributes);
};

