#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "da/Transform.h"
#include "common/WalkSprite.h"
#include "sim/PlayerUpdater.h"

using namespace common;

namespace sim {

bool PlayerUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::Transform>() &&
           entity.hasAttribute<WalkSprite>();
}

void PlayerUpdater::updateEntity(const sf::Time &deltaTime,
                                 da::Entity &entity) {
    da::Transform &transform = entity.getAttribute<da::Transform>();
    WalkSprite &walk = entity.getAttribute<WalkSprite>();
                                     
    int horz = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    int vert = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    
    transform.move(100.f * deltaTime.asSeconds() * horz,
                   100.f * deltaTime.asSeconds() * vert);
                                     
    if (horz || vert) {
        std::cout << "(" << transform.getPosition().x << ", "
                  << transform.getPosition().y << ")" << std::endl;
    }
}
    
}
