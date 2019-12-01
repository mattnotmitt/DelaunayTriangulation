//
// Created by mitt on 28/11/2019.
//

#pragma once
/**
 * Interface class allowing Vertex to be imported in classes in which Vertex is included
 */
class IVertex {
public:
    /**
     * Accessor for private member
     * @return x coordinate
     */
    virtual float getX() const = 0;
    /**
     * Accessor for private member
     * @return y coordinate
     */
    virtual float getY() const = 0;
    /**
     * Accessor for private member
     * @return z coordinate
     */
    virtual float getZ() const = 0;
    virtual int getIndex() const = 0;
};
