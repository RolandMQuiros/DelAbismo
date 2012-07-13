#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "da/Attribute.h"
#include "da/Behavior.h"
#include "da/Entity.h"
#include "da/EntityManager.h"

struct TestAttribute : public da::Attribute {
    static const char *TypeName;
    sf::Sprite sprite;
    
    TestAttribute();
};

const char *TestAttribute::TypeName = "TestAttribute";

TestAttribute::TestAttribute() :
da::Attribute(TypeName) {
    
}

class TestBehavior : public da::Behavior {
public:
    TestBehavior();
    void setTarget(sf::RenderTarget &target);
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &time, da::Entity &entity);
private:
    sf::RenderTarget *mvRenderTarget;
};

TestBehavior::TestBehavior() :
mvRenderTarget(NULL) {
    
}

void TestBehavior::setTarget(sf::RenderTarget &target) {
    mvRenderTarget = &target;
}

bool TestBehavior::isCompatible(const da::Entity &entity) const {
    if (!entity.getAttribute<TestAttribute>().expired()) {
        return true;
    }
    
    return false;
}

void TestBehavior::updateEntity(const sf::Time &time, da::Entity &entity) {
    std::shared_ptr<TestAttribute> test(entity.getAttribute<TestAttribute>());
    
    int vert = sf::Keyboard::isKeyPressed(sf::Keyboard::S) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    int horz = sf::Keyboard::isKeyPressed(sf::Keyboard::D) -
               sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    
    test->sprite.move(100.f * time.asSeconds() * horz,
                      100.f * time.asSeconds() * vert);
    
    
    if (mvRenderTarget != NULL) {
        mvRenderTarget->draw(test->sprite);
    }
}

int main(int argc, char *argv[]) {
    sf::RenderWindow app(sf::VideoMode(640, 480), "Title");
    da::EntityManager entityManager;
    
    std::shared_ptr<TestBehavior> testBehavior(new TestBehavior());
    testBehavior->setTarget(app);
    entityManager.addBehavior(testBehavior);
    
    da::EntityPtr entity = entityManager.create();
    
    TestAttribute *attr = new TestAttribute();
    sf::Texture texture;
    texture.loadFromFile("content/textures/Slamsona 3.jpg");
    attr->sprite.setTexture(texture);
    
    entity->addAttribute(da::AttributePtr(attr));
    entityManager.refresh(entity);
    
    sf::Clock frameClock;
    sf::Time frameTime;
    
    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                app.close();
            }
        }
        
        app.clear();
        try {
            entityManager.updateBehavior(frameTime, testBehavior);
        } catch (da::DAException &e) {
            std::cerr << e.message() << std::endl;
            app.close();
        }
        app.display();
        
        frameTime = frameClock.restart();
    }
}
