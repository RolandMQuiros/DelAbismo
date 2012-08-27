#include "bhvr/DepthRenderer.h"

namespace bhvr {

DepthRenderer::DepthRenderer(DepthDrawList &list) :
mvList(list) {

}

void DepthRenderer::draw(const sf::Drawable &drawable,
                         const attr::Depth &depth,
                         const sf::RenderStates &states) {
    mvList.push(drawable, depth, states);
}

}
