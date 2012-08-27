#include <gtest/gtest.h>

#include "da/Depth.h"

#include "attr/Sprite.h"
#include "attr/Transform.h"

#include "bhvr/SpriteRenderer.h"

#include "EntityEnvironment.h"

namespace test {

TEST_F(EntityEnvironment, SpriteRenderTest) {
    // Register SpriteRenderer
    State->addBehavior(new bhvr::SpriteRenderer(State->getDepthDrawList()),
                       true);
    
    // Create entity
    da::EntityPtr entity = State->createEntity();
    
    // Create Sprite attribute
    da::TexturePtr texture = 
        Game.content.load<sf::Texture>("../content/textures/Slamsona 3.jpg");
    attr::Sprite *sprite = new attr::Sprite(texture);
    entity->addAttribute(sprite);
    
    // Create Transform attribute
    entity->addAttribute(new attr::Transform());
    
    // Create Depth attribute
    entity->addAttribute(new da::Depth());
    
    State->refreshEntity(entity);
    
    // Run
    try {
        Game.run();
    } catch (unsigned int err) {
        EXPECT_EQ(0, err);
    }
}
    
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
