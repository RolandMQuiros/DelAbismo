#include "da/DepthRenderBehavior.h"

namespace da {

DepthRenderBehavior::DepthRenderBehavior(DepthDrawList &list) :
mvList(list) {
    
}

void DepthRenderBehavior::draw(const sf::Drawable &drawable,
                               const Depth &depth,
                               const sf::RenderStates &states) {
    mvList.push(drawable, depth, states);
}
    
}
