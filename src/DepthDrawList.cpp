#include <algorithm>
#include "DepthDrawList.h"

DepthDrawList::DrawRequest::DrawRequest(const DrawFunction &draw,
                                        const attr::Depth &depth,
                                        const sf::RenderStates &states) :
draw(draw),
depth(&depth),
states(states) {
    
}

bool DepthDrawList::DrawRequest::operator<(const DrawRequest &other) const {
    return depth < other.depth;
}

void DepthDrawList::push(const DrawFunction &draw,
                         const attr::Depth &depth,
                         const sf::RenderStates &states) {
    DrawRequest request(draw, depth, states);
    
    mvList.push_back(request);
}

void DepthDrawList::sort() {
    std::sort(mvList.begin(), mvList.end());
}

void DepthDrawList::clear() {
    mvList.clear();
}

void DepthDrawList::draw(sf::RenderTarget &target,
                          sf::RenderStates states) const {
    for (unsigned int i = 0; i < mvList.size(); i++) {
        mvList[i].draw(target, states);
    }
}
