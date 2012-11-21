#include <cmath>
#include <da/MathHelper.h>
#include "Polygon2d.h"

Polygon2d::Polygon2d() :
mIsRecalculate(true),
mIsConvex() {
    
}

void Polygon2d::setVertices(const sf::Vector2f *vertices,
                            unsigned int vertexCount) {
    for (unsigned int i = 0; i < vertexCount; i++) {
        addVertex(vertices[i]);
    }
}

void Polygon2d::addVertex(const sf::Vector2f &vertex) {
    mVertices.push_back(vertex);
    mIsRecalculate = true;
        
    // If this is the first vertex added, make an infinitely small bounding box
    // around it
    if (mVertices.size() == 1) {
        mBoundingBox.left = vertex.x;
        mBoundingBox.top = vertex.y;
        
        return;
    }
    
    // Resize the bounding box to encompass the entire polygon
    mBoundingBox.left = std::min(vertex.x, mBoundingBox.left);
    mBoundingBox.top = std::min(vertex.y, mBoundingBox.top);
    
    if (vertex.x > mBoundingBox.left + mBoundingBox.width) {
        mBoundingBox.width = vertex.x - mBoundingBox.left;
    }
    
    if (vertex.y > mBoundingBox.top + mBoundingBox.height) {
        mBoundingBox.height = vertex.y - mBoundingBox.top;
    }
}

sf::Vector2f Polygon2d::getVertex(unsigned int index) const {
    sf::Vector2f ret;
    if (index < mVertices.size()) {
        ret = mVertices[index];
    }
    
    return ret;
}

const std::vector<sf::Vector2f> &Polygon2d::getVertices() const {
    return mVertices;
}

sf::FloatRect Polygon2d::getBoundingBox() const {
    return mBoundingBox;
}

bool Polygon2d::isConvex() {
    // If we have a valid calculation for the current state of the polygon,
    // then just return the result of our previous calculation.
    if (!mIsRecalculate) {
        return mIsConvex;
    }
    
    // Otherwise, recalculate
    if (mVertices.size() <= 2) {
        return (mIsConvex = mIsRecalculate = false);
    }
    
    
    // For every vertex in the polygon, find the cross product of the two
    // connected edges.  The sign of the resulting magnitude should stay the
    // same for every vertex, otherwise the polygon is not convex.
    
    float angleSum = 0.f;
    bool gotNegative = false;
    bool gotPositive = false;
    for (unsigned int i = 0; i < mVertices.size(); i++) {
        unsigned int idxA = (i - 1) % mVertices.size();
        unsigned int idxB = (i + 1) % mVertices.size();
        
        sf::Vector2f segmentA = mVertices[idxA] - mVertices[i];
        sf::Vector2f segmentB = mVertices[idxB] - mVertices[i];
        
        float crossProduct = da::MathHelper::cross(segmentA.x, segmentA.y,
                                                   segmentB.x, segmentB.y);
        
        gotNegative |= crossProduct < 0.f;
        gotPositive |= crossProduct > 0.f;
        
        if (gotNegative && gotPositive) {
            break;
        }
    }
    
    mIsConvex = !(gotNegative && gotPositive);
    mIsRecalculate = false;
    
    return mIsConvex;
}

