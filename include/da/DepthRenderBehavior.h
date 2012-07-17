#ifndef DA_DEPTHRENDERBEHAVIOR_H
#define DA_DEPTHRENDERBEHAVIOR_H

#include "da/RenderBehavior.h"
#include "da/Depth.h"
#include "da/DepthDrawList.h"

namespace da {

class DepthRenderBehavior : public RenderBehavior {
public:
    DepthRenderBehavior(DepthDrawList &list);
    
protected:
    void draw(const sf::Drawable &drawable,
              const Depth &depth,
              const sf::RenderStates &states=sf::RenderStates::Default);
private:
    DepthDrawList &mvList;
};

}

#endif
