#include <SFML/Graphics/RenderStates.hpp>

#include "da/Transform.h"
#include "common/WalkSprite.h"

#include "sim/PlayerRenderer.h"

namespace sim {

bool PlayerRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::Transform>() &&
           entity.hasAttribute<common::WalkSprite>();
}

void PlayerRenderer::updateEntity(const sf::Time &deltaTime,
                                  da::Entity &entity) {
    da::Transform &transform = entity.getAttribute<da::Transform>();
    common::WalkSprite &walk = entity.getAttribute<common::WalkSprite>();
    
    walk.directions[common::WalkSprite::South].update(deltaTime);
    
    sf::RenderStates states;
    states.transform = transform.getTransform();
        
    draw(walk.directions[common::WalkSprite::South], states);
}
    
}
