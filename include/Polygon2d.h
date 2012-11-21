#ifndef POLYGON2D_H
#define POLYGON2D_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class Polygon2d {
public:
    Polygon2d();
    void setVertices(const sf::Vector2f *vertices, unsigned int vertexCount);
    void addVertex(const sf::Vector2f &vertex);
    sf::Vector2f getVertex(unsigned int index) const;
    const std::vector<sf::Vector2f> &getVertices() const;
    
    sf::FloatRect getBoundingBox() const;
    bool isConvex();
    
private:
    std::vector<sf::Vector2f> mVertices;
    sf::FloatRect mBoundingBox;
    
    /** True if a vertex was added.  When true, a call to Polygon::isConvex()
        will recalculate the convex-ness of this polygon */
    bool mIsRecalculate;
    /** True if this polygon is convex, and thus eligible for SAT */
    bool mIsConvex;
    
};

#endif
