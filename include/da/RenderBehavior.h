#ifndef DA_RENDERBEHAVIOR_H
#define DA_RENDERBEHAVIOR_H

#include <SFML/Graphics/RenderTarget.hpp>
#include "da/Behavior.h"

namespace da {

class RenderBehavior : public Behavior {
public:
    RenderBehavior();
    void setTarget(sf::RenderTarget &target);
    
protected:    
    void draw(const sf::Drawable &drawable,
              const sf::RenderStates &states=sf::RenderStates::Default);
    void draw(const sf::Vertex *vertices, unsigned int vertexCount,
              sf::PrimitiveType type,
              const sf::RenderStates &states=sf::RenderStates::Default);

private:
    sf::RenderTarget *mvTarget;
};

}

#endif
