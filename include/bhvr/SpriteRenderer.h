#ifndef BHVR_SPRITERENDERER_H
#define BHVR_SPRITERENDERER_H

#include "da/DepthRenderBehavior.h"

namespace bhvr {

class SpriteRenderer : public da::DepthRenderBehavior {
public:
    SpriteRenderer(da::DepthDrawList &list);

protected:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &deltaTime, da::Entity &entity);
};

}

#endif
