#include <cmath>
#include <cstdlib>
#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>

#include <gtest/gtest.h>
#include "EntityEnvironment.h"

#include <da/MathHelper.h>
#include <da/twod/Spatial.h>
#include <da/twod/attr/Transform.h>
#include <da/twod/attr/Depth.h>
#include <da/twod/bhvr/SpatialRenderer.h>

#define private public

#include "attr/DirectedAnimation.h"
#include "bhvr/DirectedAnimation.h"

using namespace test;

da::attr::Transform *xform;
attr::DirectedAnimation *dirAnim;
sf::Text text;

void mover(da::Game &game, const sf::Time &delta) {
    int vert = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    int horz = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    
    if (vert || horz) {
        float theta = atan2(vert, horz);
        
        xform->move(horz * delta.asSeconds() * 100.f,
                    vert * delta.asSeconds() * 100.f);
        
        dirAnim->setDirection(theta);
        dirAnim->getAnimation().play();
    } else {
        dirAnim->getAnimation().stop();
    }
}

void render(sf::RenderTarget &target, sf::RenderStates states) {
    std::stringstream ss;
    ss << "Direction: " << dirAnim->getDirection() << std::endl
       << "Index: " << dirAnim->mIndex;
    
    text.setString(ss.str());
    
    target.draw(text);
}

TEST_F(EntityEnvironment, DirectedAnimationTest) {
    da::bhvr::SpatialRenderer *renderer = new da::bhvr::SpatialRenderer(Game);
    State->addBehavior(renderer, true);
    
    renderer->registerSpatial<bhvr::DirectedAnimation::Spatial>();
    
    State->addBehavior(new bhvr::DirectedAnimation);
    
    // Add updater
    std::function<void (da::Game &, const sf::Time &)> updater(mover);
    State->addUpdater(updater);
    std::function<void (sf::RenderTarget &target, 
                        sf::RenderStates state)> rend(render);
    State->addRenderer(rend);
    
    // Create entity
    da::EntityPtr entity = State->createEntity();
    xform = new da::attr::Transform;
    xform->setPosition(320.f, 240.f);
    entity->addAttribute(xform);
    entity->addAttribute(new da::attr::Depth);
    
    // Create DirectedAnimation
    dirAnim = new attr::DirectedAnimation;
    
    da::TexturePtr texture = Game.content.load<sf::Texture>(
        "directionTest.png");
    
    for (unsigned int i = 0; i < 8; i++) {
        da::Animation temp;
        temp.setTexture(texture);
        
        temp.addFrame(sf::IntRect(0, 32 * i, 32, 32),
                      sf::seconds(1.f));
        temp.addFrame(sf::IntRect(32, 32 * i, 32, 32),
                      sf::seconds(1.f));
        temp.play();
        
        dirAnim->addAnimation(temp);
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
            
            temp.addFrame(sf::IntRect(0, 32 * i, 32, 32),
                          sf::seconds(1.f));
            temp.addFrame(sf::IntRect(32, 32 * i, 32, 32),
                          sf::seconds(1.f));
            temp.play();
            
            anim->addAnimation(temp);
        }
        
        bmEntity->addAttribute(anim);
        State->refreshEntity(bmEntity);
    }
    
    text.setCharacterSize(12);
    text.setPosition(0.f, 24.f);
    
    // Run
    try {
        Game.run();
        
    } catch (unsigned int err) {
        EXPECT_EQ(0, err);
        
        delete xform;
        delete dirAnim;
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
