#ifndef BHVR_DEPTHRENDERER_H
#define BHVR_DEPTHRENDERER_H

#include <functional>

#include "da/EntityBehavior.h"

namespace bhvr {

class DepthRenderer : public da::EntityBehavior {
public:
    DepthRenderer();
    
protected:
    void updateEntity(da::Entity &entity);
    void end();
    
private:
    struct DrawRequest {
        std::function<void(sf::RenderTarget &target,
                           sf::RenderStates states)> draw;
        const attr::Depth *depth;
    };
    
    std::vector<DrawRequest> mDrawList; 
};

}

#endif
