#include "da/RenderBehavior.h"

namespace da {

RenderBehavior::RenderBehavior() :
mvTarget(NULL) {
    
}

void RenderBehavior::setTarget(sf::RenderTarget &target) {
    mvTarget = &target;
}

void RenderBehavior::draw(const sf::Drawable &drawable,
                          const sf::RenderStates &states) {
    if (mvTarget != NULL) {
        mvTarget->draw(drawable, states);
    }
}

void RenderBehavior::draw(const sf::Vertex *vertices, unsigned int vertexCount,
                          sf::PrimitiveType type,
                          const sf::RenderStates &states) {
    if (mvTarget != NULL) {
        mvTarget->draw(vertices, vertexCount, type, states);
    }
}

}
