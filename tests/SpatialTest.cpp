#include <gtest/gtest.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "EntityEnvironment.h"

#include "Spatial.h"
#include "attr/Transform.h"
#include "attr/Depth.h"
#include "bhvr/SpatialRenderer.h"

namespace test {
    
    struct SpriteAttribute : public da::Attribute<SpriteAttribute> {
        sf::Sprite sprite;
    };
    
    class TestSpatial : public Spatial<TestSpatial> {
    public:
        TestSpatial(da::Entity &entity);
        
        static SpatialBase *create(da::Entity &entity);
        
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    private:
        sf::Sprite &mSprite;
    };
    
    TestSpatial::TestSpatial(da::Entity &entity) :
    Spatial<TestSpatial>(entity),
    mSprite(entity.getAttribute<SpriteAttribute>().sprite) {
        
    }
    
    SpatialBase *TestSpatial::create(da::Entity &entity) {
        if (entity.hasAttribute<SpriteAttribute>()) {
            return new TestSpatial(entity);
        }
        return NULL;
    }
    
    void TestSpatial::draw(sf::RenderTarget &target,
                           sf::RenderStates states) const {
        int horz = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
                   sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        int vert = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
                   sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        
        mSprite.move(horz, vert);
        
        target.draw(mSprite, states);
    }
    
    da::EntityPtr createSpatialEntity(da::Game &game, TestState *state) {
        // Create entity
        da::EntityPtr entity = state->createEntity();
        
        // Create Sprite Attribute
        da::TexturePtr texture = 
            game.content.load<sf::Texture>("../content/textures/Slamsona 3.jpg");
        SpriteAttribute *sprite = new SpriteAttribute;
        sprite->sprite.setTexture(*texture);
        sprite->sprite.setPosition(320.f, 240.f);
        entity->addAttribute(sprite);
        
        // Create Transform attribute
        entity->addAttribute(new attr::Transform());
        
        // Create Depth attribute
        entity->addAttribute(new attr::Depth());
        
        state->refreshEntity(entity);
        
        return entity;
    }
    
    
    TEST_F(EntityEnvironment, SpatialTest) {
        // Register SpatialRenderer
        bhvr::SpatialRenderer *renderer = new bhvr::SpatialRenderer(Game);
        State->addBehavior(renderer, true);
        
        renderer->registerSpatial<TestSpatial>();
        
        da::EntityPtr entity1 = createSpatialEntity(Game, State);
        da::EntityPtr entity2 = createSpatialEntity(Game, State);
        
        entity2->getAttribute<SpriteAttribute>().sprite.setTexture(
            *Game.content.load<sf::Texture>("../content/textures/niccage.jpg")
        );
        
        entity2->getAttribute<SpriteAttribute>().sprite.setPosition(0.f, 0.f);
        entity2->getAttribute<attr::Depth>().pushDepth(1);
        
        // THE BUG: the std::set in SpatialRenderer isn't inserting additional
        // entities properly.  entity2 is overwriting entity1.
        
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
