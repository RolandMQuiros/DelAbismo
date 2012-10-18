#include <da/twod/attr/Depth.h>
#include "bhvr/SpriteRenderer.h"

namespace bhvr {

da::SpatialBase *SpriteRenderer::Spatial::create(da::Entity &entity) {
    if (entity.hasAttribute<attr::Sprite>()) {
        return new Spatial(entity);
    }
    
    return NULL;
}

SpriteRenderer::Spatial::Spatial(da::Entity &entity) :
da::Spatial<Spatial>(entity),
mTransform(entity.getAttribute<da::attr::Transform>()),
mSprite(entity.getAttribute<attr::Sprite>()) {
    
}

void SpriteRenderer::Spatial::draw(sf::RenderTarget &target,
                                   sf::RenderStates states) const {
    states.transform *= mTransform.getTransform();
    
    target.draw(mSprite, states);
}

bool SpriteRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::attr::Transform>() &&
           entity.hasAttribute<da::attr::Depth>() &&
           entity.hasAttribute<attr::Sprite>();
}

void SpriteRenderer::updateEntities(da::EntityGroup &entities) {
    
}

}
