//
// Created by matt on 17/11/2019.
//
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "Mesh.hpp"

std::ostream &operator<<(std::ostream &os, const Mesh &mesh) {
    os << "The mesh has " << mesh.vertices.size() << " vertices.";
    return os;
}

const std::map<int, Vertex> &Mesh::getVertices() const {
    return vertices;
}

void Mesh::setVertices(const std::map<int, Vertex> &vertices) {
    Mesh::vertices = vertices;
}

bool checkLineLength(std::string line, int length) {
    std::istringstream iss(line);
    return length == std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
}

void Mesh::loadFile(const std::string &filePath) {
    std::ifstream infile(filePath.c_str(), std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open input file.");
    }
    std::string line;
    int lineNum = 1;
    try {
        // parse definition line
        struct propStruct {
            int vertexCount;
            int cellCount;
            int cellPoints;
            int dimensions;
            int attributes;
            bool done;
        } props = {.vertexCount=0, .done=false};
        int index = -2;
        std::map<int, Vertex> newVertices;
        while (index < props.vertexCount-1) { // Get line from file and store in line variable
            std::getline(infile, line);
            if (line == "\r" || line == "\n") continue; // Skip line if only contains newline
            std::istringstream iss(line);
            if (iss.str().empty()) continue; // Skip line if stream is empty
            if (!props.done) {
                if (checkLineLength(line, 3)) {
                    iss >> props.vertexCount >> props.dimensions >> props.attributes;
                    props.done = true;
                    continue;
                } else {
                    throw std::runtime_error("First non-empty line of file is not a valid declaration.");
                }
            }
            if (!checkLineLength(line, props.dimensions + props.attributes + 1)) {
                throw std::runtime_error("Vertex declaration has missing parameters");
            }
            iss >> index; // read in type and index values
            Vertex vec(index);
            iss >> vec;
            newVertices.insert(std::pair<int, Vertex>(index, vec));
            lineNum++;
        }
        setVertices(newVertices);
        std::map<int, Triangle> newTriangles;
        index = -2;
        props.done = false;
        while (index < props.cellCount-1) { // Get line from file and store in line variable
            std::getline(infile, line);
            if (line == "\r" || line == "\n") continue; // Skip line if only contains newline
            std::istringstream iss(line);
            if (iss.str().empty()) continue; // Skip line if stream is empty
            if (!props.done) {
                if (checkLineLength(line, 3)) {
                    iss >> props.cellCount >> props.cellPoints >> props.attributes;
                    if (props.cellPoints != 3) {
                        throw std::runtime_error("This program only supports cells consisting of 3 points.");
                    }
                    props.done = true;
                    continue;
                } else {
                    throw std::runtime_error("First non-empty line of file is not a valid declaration.");
                }
            }
            if (!checkLineLength(line, props.cellPoints + props.attributes + 1)) {
                throw std::runtime_error("Vertex declaration has missing parameters");
            }
            iss >> index; // read in type and index values
            Triangle tri(index);
            iss >> tri;
            newTriangles.insert(std::pair<int, Triangle>(index, tri));
            lineNum++;
        }
        setTriangles(newTriangles);
    } catch (const std::runtime_error &msg) {
        // Throw error with information about where issue is in file
        std::stringstream errorMsg;
        errorMsg << "Error on line " << lineNum << " in " << filePath << ": " << msg.what();
        throw std::runtime_error(errorMsg.str());
    }
}

const std::map<int, Triangle> &Mesh::getTriangles() const {
    return triangles;
}

void Mesh::setTriangles(const std::map<int, Triangle> &triangles) {
    Mesh::triangles = triangles;
}
