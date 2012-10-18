#include "spatial/Sprite.h"

namespace spatial {

da::SpatialBase *Sprite::create(da::Entity &entity) {
    if (entity.hasAttribute<attr::Sprite>()) {
        return new Sprite(entity);
    }
    
    return NULL;
}

Sprite::Sprite(da::Entity &entity) :
da::Spatial<Sprite>(entity),
mTransform(entity.getAttribute<da::attr::Transform>()),
mSprite(entity.getAttribute<attr::Sprite>()) {
    
}

void Sprite::draw(sf::RenderTarget &target,
                                   sf::RenderStates states) const {
    states.transform *= mTransform.getTransform();    
    target.draw(mSprite, states);
}


}
