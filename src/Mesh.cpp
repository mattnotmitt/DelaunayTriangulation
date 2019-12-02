//
// Created by matt on 17/11/2019.
//
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <Eigen/Dense>
#include <set>
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
        } props = {0, 0, 0, false};
        int index = -2;
        std::map<int, Vertex> newVertices;
        while (index < props.vertexCount - 1) { // Get line from file and store in line variable
            std::getline(ifs, line);
            int length = Utils::lineLength(line);
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
                errorMsg << "Vector declaration has " << length << " parameters, expecting "
                         << mesh.dimensions + mesh.vertexAttributes + 1;
                throw std::runtime_error(errorMsg.str());
            }
            iss >> index; // read in type and index values
            Vertex vec(index, mesh.dimensions, &mesh);
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
        while (index < props.cellCount - 1) { // Get line from file and store in line variable
            if (props.done) {
                std::getline(ifs, line);
            }
            int length = Utils::lineLength(line);
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
                errorMsg << "Cell declaration has " << length << " parameters, expecting "
                         << props.cellPoints + mesh.triangleAttributes + 1;
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

std::vector<Vec> Mesh::resolvePoints(std::vector<int> pointIndices) {
    std::vector<Vec> points;
    for (int i = 0; i < pointIndices.size(); i++) {
        try {
            Vertex vert = vertices.at(pointIndices[i]);
            points.push_back(vert.getVec());
        } catch (const std::out_of_range &msg) {
            std::stringstream ss;
            ss << "Vertex " << i << " does not exist.";
            throw std::runtime_error(ss.str());
        }
    }
    return points;
}

int Mesh::containingTriangle(double x, double y) {
    Eigen::Vector2d p(x, y);
    for (int i = 0; i < triangles.size(); i++) {
        if (triangles[i].containsPoint(p)) {
            return i;
        }
    }
    return -1;
}

bool Mesh::isDelaunay() {
    bool is = true;
    if (triangles.empty())
        throw std::runtime_error("Cannot check if mesh is Delaunay Triangulation, no triangles defined.");
    for (int i = 0; i < vertices.size(); i++) {
        Eigen::Vector2d vert(vertices[i].getVec().getX(), vertices[i].getVec().getY());
        for (int j = 0; j++ < triangles.size(); j++) {
            if (triangles[j].circumcircleContainsPoint(vert)) {
                //std::cout << j << ": " << i << ": " << vertices[i] << ": " << triangles[j].getCc().x << "," << triangles[j].getCc().y << "," << triangles[j].getCc().radius << std::endl;
                //std::cout << triangles[j] << std::endl;
                is = false;
                return is;
            }
        }
    }
    return is;
}

std::vector<std::pair<int, int> > Mesh::newEdges(int tri, const std::vector<int> &vert) {
    std::vector<Mesh::edge > nEdges;
    nEdges.push_back(Mesh::edge(vert[0], vert[1]));
    nEdges.push_back(Mesh::edge(vert[1], vert[2]));
    nEdges.push_back(Mesh::edge(vert[0], vert[2]));
    if (edges.find(nEdges[0]) == edges.end()) {
        edges.insert(std::pair<Mesh::edge, std::vector<int> >(nEdges[0], std::vector<int>(1, tri)));
    } else edges[nEdges[0]].push_back(tri);
    if (edges.find(nEdges[1]) == edges.end()) {
        edges.insert(std::pair<Mesh::edge, std::vector<int> >(nEdges[1], std::vector<int>(1, tri)));
    } else edges[nEdges[1]].push_back(tri);
    if (edges.find(nEdges[2]) == edges.end()) {
        edges.insert(std::pair<Mesh::edge, std::vector<int> >(nEdges[2], std::vector<int>(1, tri)));
    } else edges[nEdges[2]].push_back(tri);
    return nEdges;
}

const std::map<Mesh::edge, std::vector<int> > &Mesh::getEdges() const {
    return edges;
}

std::vector<int> Mesh::adjacentTriangles(int triInd) {
    std::vector<int> vert = triangles[triInd].getVertices();
    Mesh::edge paira(vert[0], vert[1]), pairb(vert[1], vert[2]), pairc(vert[0], vert[2]);
    std::set<int> adjSet;
    adjSet.insert(edges[paira].begin(), edges[paira].end());
    adjSet.insert(edges[pairb].begin(), edges[pairb].end());
    adjSet.insert(edges[pairc].begin(), edges[pairc].end());
    std::vector<int> adj(adjSet.begin(), adjSet.end());
    adj.erase(std::find(adj.begin(), adj.end(), triInd));
    return adj;
}

void Mesh::removeEdges(int triInd, const std::vector<std::pair<int, int> > &rEdge) {
    for (int i = 0; i < rEdge.size(); i++) {
        std::vector<int> inds = edges[rEdge[i]];
        // Sorry about this but you won't give us auto :angery:
        __gnu_cxx::__normal_iterator<int *, std::vector<int> > ind = std::find(inds.begin(), inds.end(), triInd);
        if (ind != inds.end()) inds.erase(ind);
    }
}

void Mesh::recalcCircum(int vertInd) {
    std::vector<int> updTris = vertTri[vertInd];
    for (int i = 0; i < updTris.size(); i++) {
        triangles[updTris[i]].calcCircumcircle();
    }
}

void Mesh::updateVertTri(int triInd, std::vector<int> vertInds) {
    for (int i = 0; i < vertInds.size(); i++) {
        if (vertTri.find(vertInds[i]) == vertTri.end()) {
            vertTri.insert(std::pair<int, std::vector<int> >(vertInds[i], std::vector<int>(1, triInd)));
        } else vertTri[vertInds[i]].push_back(triInd);
    }
}

void Mesh::removeVertTri(int triInd, std::vector<int> rVertInds) {
    for (int i = 0; i < rVertInds.size(); i++) {
        std::vector<int> inds = vertTri[rVertInds[i]];
        __gnu_cxx::__normal_iterator<int *, std::vector<int> > ind = std::find(inds.begin(), inds.end(), triInd);
        if (ind != inds.end()) inds.erase(ind);
    }
}

bool Mesh::operator==(const Mesh &rhs) const {
    return vertexAttributes == rhs.vertexAttributes &&
           triangleAttributes == rhs.triangleAttributes &&
           dimensions == rhs.dimensions &&
           vertices == rhs.vertices &&
           triangles == rhs.triangles &&
           edges == rhs.edges &&
           vertTri == rhs.vertTri;
}

bool Mesh::operator!=(const Mesh &rhs) const {
    return !(rhs == *this);
}
