#include <algorithm>

#include "da/DAException.h"
#include "da/Transform.h"
#include "common/WalkSprite.h"
#include "sim/CharacterRenderer.h"
#include "sim/PlayerRenderer.h"
#include "sim/PlayerUpdater.h"
#include "sim/Sim.h"

namespace sim {

std::shared_ptr<CharacterRenderer> renderer;
std::shared_ptr<PlayerUpdater> updater;
    
Sim::Sim(da::Game &game) :
mvGame(game) {
}

void Sim::initialize() {
    renderer = std::shared_ptr<CharacterRenderer>(
        new CharacterRenderer(mvDrawList)
    );
    renderer->setTarget(mvGame);
    
    updater = std::shared_ptr<PlayerUpdater>(new PlayerUpdater());
    
    mvEntities.addBehavior(renderer);
    mvEntities.addBehavior(updater);
    
    createCharacter();
}

void Sim::dispose() {
    
}

void Sim::update() {
    updater->update(mvGame.getFrameTime());
}

void Sim::draw() {
    renderer->update(mvGame.getFrameTime());
    
    mvDrawList.sort();
    mvGame.draw(mvDrawList);
    mvDrawList.clear();
}

da::EntityPtr Sim::createCharacter() {
    da::EntityPtr entity = mvEntities.create();
    
    // TODO: Using the bare pointer overload causes a segfault on exit. Figure
    // this shit out
    entity->addAttribute(new da::Transform()); // Segfaults
    entity->addAttribute(da::AttributePtr(new da::Depth()));  // Doesn't
    
    da::TexturePtr texture = mvGame.content.load<sf::Texture>(
        "content/textures/Slamsona 3.jpg"
    );
    
    entity->addAttribute(da::AttributePtr(new common::WalkSprite(
        texture, sf::Vector2i(), sf::Vector2i(64, 64), 5
    )));
    
    mvEntities.refresh(entity);
    return entity;
}

}
