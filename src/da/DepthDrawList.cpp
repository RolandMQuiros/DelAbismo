#include <algorithm>
#include "da/DepthDrawList.h"

namespace da {
    
bool DepthDrawList::DrawRequest::operator<(const DrawRequest &other) const {
    return *depth < *other.depth;
}

void DepthDrawList::push(const sf::Drawable &drawable,
                         const Depth &depth,
                         const sf::RenderStates &states) {
    DrawRequest request = {
        &drawable, &depth, states
    };
    
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
        target.draw(*mvList[i].drawable, mvList[i].states);
    }
}

}