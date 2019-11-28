//
// Created by matt on 26/11/2019.
//

#pragma once
#include "IVertex.hpp"

class IMesh {
public:
    virtual std::vector<IVertex*> resolvePoints(std::vector<int> pointIndices) = 0;
    virtual void recalcCircum(int pointInd) = 0;
    virtual std::vector<std::pair<int, int> > newEdges(int triInd, const std::vector<int> &vert) = 0;
    virtual void removeEdges(int triInd, const std::vector<std::pair<int, int> > &rEdge) = 0;
    virtual void updateVertTri(int triInd, std::vector<int> vertInds) = 0;
    virtual void removeVertTri(int triInd, std::vector<int> rVertInds) = 0;
};

