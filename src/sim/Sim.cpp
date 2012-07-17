#include <algorithm>

#include "da/DAException.h"
#include "da/Transform.h"
#include "common/WalkSprite.h"
#include "sim/PlayerRenderer.h"
#include "sim/PlayerUpdater.h"
#include "sim/Sim.h"

namespace sim {

std::shared_ptr<PlayerRenderer> renderer;
std::shared_ptr<PlayerUpdater> updater;
    
Sim::Sim(da::Game &game) :
mvGame(game) {
}

void Sim::initialize() {
    renderer = std::shared_ptr<PlayerRenderer>(new PlayerRenderer());
    renderer->setTarget(mvGame);
    
    updater = std::shared_ptr<PlayerUpdater>(new PlayerUpdater());
    
    mvEntities.addBehavior(renderer);
    mvEntities.addBehavior(updater);
    
    da::EntityPtr entity = mvEntities.create();
    
    da::TexturePtr texture = mvGame.content.load<sf::Texture>("content/textures/Slamsona 3.jpg");
    if (!texture) {
        throw da::DAException(__RELFILE__, __LINE__, "sim::Sim::intialize()",
                              "Texture load failed!");
    }
    
    entity->addAttribute(
        da::AttributePtr(new da::Transform())
    );
    
    entity->addAttribute(
        da::AttributePtr(
            new common::WalkSprite(texture, sf::Vector2i(),
                                   sf::Vector2i(16, 16), 3)
        )
    );
    
    mvEntities.refresh(entity);
}

void Sim::dispose() {
    
}

void Sim::update() {
    updater->update(mvGame.getFrameTime());
}

void Sim::draw() {
    renderer->update(mvGame.getFrameTime());
}
    
}
