//
// Created by matt on 26/11/2019.
//

#pragma once


class IMesh {
    //virtual void recalcCircum(int triangleIndex) = 0;
public:
    virtual std::vector<Vertex> resolvePoints(std::vector<int> pointIndices) = 0;
};

