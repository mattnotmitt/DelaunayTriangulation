//
// Created by matt on 17/11/2019.
//
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "utils.hpp"
#include "Mesh.hpp"

const std::map<int, Vertex> &Mesh::getVertices() const {
    return vertices;
}

void Mesh::setVertices(const std::map<int, Vertex> &vertices) {
    Mesh::vertices = vertices;
}

const std::map<int, Triangle> &Mesh::getTriangles() const {
    return triangles;
}

void Mesh::setTriangles(const std::map<int, Triangle> &tri) {
    Mesh::triangles = tri;
}

int Mesh::getVertexAttributes() const {
    return vertexAttributes;
}

void Mesh::setVertexAttributes(int verAttr) {
    Mesh::vertexAttributes = verAttr;
}

int Mesh::getTriangleAttributes() const {
    return triangleAttributes;
}

void Mesh::setTriangleAttributes(int triAttr) {
    Mesh::triangleAttributes = triAttr;
}

int Mesh::getDimensions() const {
    return dimensions;
}

void Mesh::setDimensions(int dim) {
    Mesh::dimensions = dim;
}

std::ifstream &operator>>(std::ifstream &ifs, Mesh &mesh) {
    std::string line;
    int lineNum = 1;
    try {
        // parse definition line
        struct propStruct {
            int vertexCount;
            int cellCount;
            int cellPoints;
            bool done;
        } props = {.vertexCount=0, .cellCount=0, .done=false};
        int index = -2;
        std::map<int, Vertex> newVertices;
        while (index < props.vertexCount-1) { // Get line from file and store in line variable
            std::getline(ifs, line);
            int length = utils::lineLength(line);
            if (line == "\r" || line == "\n") continue; // Skip line if only contains newline
            std::istringstream iss(line);
            if (iss.str().empty()) continue; // Skip line if stream is empty
            if (!props.done) {
                if (length == 3) {
                    iss >> props.vertexCount >> mesh.dimensions >> mesh.vertexAttributes;
                    props.done = true;
                    lineNum++;
                    continue;
                } else {
                    throw std::runtime_error("First non-empty line of file is not a valid declaration.");
                }
            }
            if (length != mesh.dimensions + mesh.vertexAttributes + 1) {
                std::stringstream errorMsg;
                errorMsg << "Vector declaration has " << length << " parameters, expecting " << mesh.dimensions + mesh.vertexAttributes + 1;
                throw std::runtime_error(errorMsg.str());
            }
            iss >> index; // read in type and index values
            Vertex vec(index, mesh.dimensions);
            iss >> vec;
            newVertices.insert(std::pair<int, Vertex>(index, vec));
            lineNum++;
        }
        mesh.setVertices(newVertices);
        std::getline(ifs, line);
        if (ifs.eof()) {
            return ifs; // Is node file, does not have any defined triangles
        };
        std::map<int, Triangle> newTriangles;
        index = -2;
        props.done = false;
        while (index < props.cellCount-1) { // Get line from file and store in line variable
            if (props.done) {
                std::getline(ifs, line);
            }
            int length = utils::lineLength(line);
            if (line == "\r" || line == "\n") continue; // Skip line if only contains newline
            std::istringstream iss(line);
            if (iss.str().empty()) continue; // Skip line if stream is empty
            if (!props.done) {
                if (length == 3) {
                    iss >> props.cellCount >> props.cellPoints >> mesh.triangleAttributes;
                    if (props.cellPoints != 3) {
                        throw std::runtime_error("This program only supports cells consisting of 3 points.");
                    }
                    props.done = true;
                    lineNum++;
                    continue;
                } else {
                    throw std::runtime_error("Invalid cell property line.");
                }
            }
            if (length != props.cellPoints + mesh.triangleAttributes + 1) {
                std::stringstream errorMsg;
                errorMsg << "Cell declaration has " << length << " parameters, expecting " << props.cellPoints + mesh.triangleAttributes + 1;
                throw std::runtime_error(errorMsg.str());
            }
            iss >> index; // read in type and index values
            Triangle tri(index, &mesh);
            iss >> tri;
            newTriangles.insert(std::pair<int, Triangle>(index, tri));
            lineNum++;
        }
        mesh.setTriangles(newTriangles);
        return ifs;
    } catch (const std::runtime_error &msg) {
        // Throw error with information about where issue is in file
        std::stringstream errorMsg;
        errorMsg << "Error on line " << lineNum << ": " << msg.what();
        throw std::runtime_error(errorMsg.str());
    }
}

std::ofstream &operator<<(std::ofstream &ofs, Mesh &mesh) {
    std::stringstream ss;
    ss << mesh.vertices.size() << " " << mesh.dimensions << " " << mesh.vertexAttributes;
    ofs << ss.str().c_str() << "\n";
    for (int i = 0; i < mesh.vertices.size(); i++) {
        ofs << mesh.vertices.at(i);
    }
    if (!mesh.triangles.empty()) {
        ss.str("");
        ss << mesh.triangles.size() << " " << 3 << " " << mesh.triangleAttributes;
        ofs << ss.str().c_str() << "\n";
        for (int i = 0; i < (int) mesh.triangles.size(); i++) {
            ofs << mesh.triangles.at(i);
        }
    }
    return ofs;
}

std::vector<Vertex> Mesh::resolvePoints(std::vector<int> pointIndices) {
    std::vector<Vertex> points(3);
    for (int i = 0; i < 3; i++) {
        points.push_back(vertices[pointIndices[i]]);
    }
    return points;
}

int Mesh::containingTriangle(float x, float y) {
    return 0;
}


