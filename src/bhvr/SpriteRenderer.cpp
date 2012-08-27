#include "attr/Sprite.h"
#include "bhvr/SpriteRenderer.h"

namespace bhvr {

SpriteRenderer::SpriteRenderer(da::DepthDrawList &list) :
da::DepthRenderBehavior(list) {

}

bool SpriteRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::Depth>() &&
           entity.hasAttribute<attr::Sprite>();
}

void SpriteRenderer::updateEntity(const sf::Time &deltaTime,
                                  da::Entity &entity) {
    da::Depth &depth = entity.getAttribute<da::Depth>();
    attr::Sprite &sprite = entity.getAttribute<attr::Sprite>();
    
    draw(sprite, depth, sprite.getRenderStates());
}

}
