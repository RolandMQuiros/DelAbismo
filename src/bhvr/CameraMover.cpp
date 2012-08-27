#include <SFML/System/Vector2.hpp>

#include "attr/Camera.h"
#include "attr/Transform.h"
#include "bhvr/CameraMover.h"

namespace bhvr {

bool CameraMover::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<attr::Camera>();
}

void CameraMover::updateEntity(const sf::Time &deltaTime, da::Entity &entity) {
    attr::Camera &camera = entity.getAttribute<attr::Camera>();
    
    sf::Vector2f dp = camera.view.getCenter() - camera.destination;
    dp.x *= deltaTime.asSeconds() * camera.speed;
    dp.y *= deltaTime.asSeconds() * camera.speed;
    
    camera.view.move(dp);
    camera.target.setView(camera.view);
}

}
