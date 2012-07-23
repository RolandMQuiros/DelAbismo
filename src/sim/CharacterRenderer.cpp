#include <cmath>
#include <algorithm>

#include <iostream>

#include "da/Depth.h"
#include "da/Transform.h"
#include "common/WalkSprite.h"

#include "sim/CharacterRenderer.h"

namespace sim {

CharacterRenderer::CharacterRenderer(da::DepthDrawList &list) :
da::DepthRenderBehavior(list) {
    
}

bool CharacterRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::Depth>() &&
           entity.hasAttribute<da::Transform>() &&
           entity.hasAttribute<common::WalkSprite>();
}

void CharacterRenderer::updateEntity(const sf::Time &deltaTime,
                                     da::Entity &entity) {
    da::Depth &depth = entity.getAttribute<da::Depth>();
    da::Transform &transform = entity.getAttribute<da::Transform>();
    common::WalkSprite &walk = entity.getAttribute<common::WalkSprite>();
    
    float dx = transform.getPosition().x - walk.previousPosition.x;
    float dy = transform.getPosition().y - walk.previousPosition.y;
    float theta = atan2(dy, dx) + da::MathHelper::Pi;
    
    walk.previousPosition = transform.getPosition();
    
    common::WalkSprite::Direction direction = (common::WalkSprite::Direction)
        (common::WalkSprite::DirectionCount * (theta / da::MathHelper::TwoPi));
    if (direction >= common::WalkSprite::DirectionCount) {
        direction = (common::WalkSprite::Direction)(common::WalkSprite::DirectionCount - 1);
    }
    
    std::cout << direction << std::endl;
    
    sf::RenderStates states;
    states.transform = transform.getTransform();
    
    draw(walk.directions[direction], depth, states);
}

}
