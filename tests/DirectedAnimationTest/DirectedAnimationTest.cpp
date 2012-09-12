#include <cmath>
#include <cstdlib>

#include <SFML/Window/Keyboard.hpp>
#include <gtest/gtest.h>
#include "EntityEnvironment.h"

#include <da/MathHelper.h>
#include <da/twod/Spatial.h>
#include <da/twod/attr/Transform.h>
#include <da/twod/attr/Depth.h>
#include <da/twod/bhvr/SpatialRenderer.h>

#include "attr/DirectedAnimation.h"
#include "bhvr/DirectedAnimation.h"

using namespace test;

da::attr::Transform *xform;

void mover(const sf::Time &delta) {
    int vert = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    int horz = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    
    if (vert || horz) {
        float theta = atan2(vert, horz);
        
        xform->move(horz * delta.asSeconds() * 100.f,
                    vert * delta.asSeconds() * 100.f);
        
        xform->setRotation(da::MathHelper::toDegrees(theta));
    }
}

TEST_F(EntityEnvironment, DirectedAnimationTest) {
    da::bhvr::SpatialRenderer *renderer = new da::bhvr::SpatialRenderer(Game);
    State->addBehavior(renderer, true);
    
    renderer->registerSpatial<bhvr::DirectedAnimation::Spatial>();
    
    State->addBehavior(new bhvr::DirectedAnimation);
    
    // Add updater
    std::function<void (const sf::Time &)> updater(mover);
    State->addUpdater(updater);
    
    // Create entity
    da::EntityPtr entity = State->createEntity();
    xform = new da::attr::Transform;
    xform->setPosition(320.f, 240.f);
    entity->addAttribute(xform);
    entity->addAttribute(new da::attr::Depth);
    
    // Create DirectedAnimation
    attr::DirectedAnimation *dirAnim = new attr::DirectedAnimation;
    
    da::TexturePtr texture = Game.content.load<sf::Texture>(
        "../../content/textures/directionTest.png");
    
    for (unsigned int i = 0; i < 8; i++) {
        da::Animation temp;
        temp.setTexture(texture);
        temp.setSecondsPerFrame(1.f);
        temp.setLoop(-1);
        
        temp.addFrame(sf::IntRect(0, 32 * i, 32, 32));
        temp.addFrame(sf::IntRect(32, 32 * i, 32, 32));
        
        dirAnim->animations.push_back(temp);
        dirAnim->animations.back().play();
    }
    entity->addAttribute(dirAnim);
    
    State->refreshEntity(entity);
    
    // Benchmark entities
    for (unsigned int i = 0; i < 10000; i++) {
        da::EntityPtr bmEntity = State->createEntity();
        
        da::attr::Transform *transform = new da::attr::Transform;
        
        float x = rand() % 640;
        float y = rand() % 480;
        transform->setPosition(x, y);
        bmEntity->addAttribute(transform);
        
        bmEntity->addAttribute(new da::attr::Depth);
        
        attr::DirectedAnimation *anim = new attr::DirectedAnimation;
        for (unsigned int i = 0; i < 8; i++) {
            da::Animation temp;
            temp.setTexture(texture);
            temp.setSecondsPerFrame(1.f);
            temp.setLoop(-1);
            
            temp.addFrame(sf::IntRect(0, 32 * i, 32, 32));
            temp.addFrame(sf::IntRect(32, 32 * i, 32, 32));
            
            anim->animations.push_back(temp);
            anim->animations.back().play();
        }
        
        bmEntity->addAttribute(anim);
        State->refreshEntity(bmEntity);
    }
    
    // Run
    try {
        Game.run();
        
    } catch (unsigned int err) {
        EXPECT_EQ(0, err);
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
