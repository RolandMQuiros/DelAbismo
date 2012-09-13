#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <da/Animation.h>
#include <sstream>

int main() {
    sf::RenderWindow app(sf::VideoMode(640, 480), "Animation benchtest");
    
    sf::Clock frameClock;
    sf::Time frameTime;
    
    sf::Time frameCount;
    sf::Text frameDisplay;
    
    da::TexturePtr texture(new sf::Texture);
    texture->loadFromFile("directionTest.png");
    
    da::Animation animation;
    animation.setTexture(texture);
    animation.setSecondsPerFrame(0.4f);
    animation.addFrame(sf::IntRect(0, 0, 32, 32));
    animation.addFrame(sf::IntRect(32, 0, 32, 32));
    animation.play();
    
    sf::RenderStates matrices[10000];
    sf::Transformable temp;
    
    for (unsigned int i = 0; i < 10000; i++) {
        temp.setPosition(rand() % 640, rand() % 480);
        matrices[i].transform = temp.getTransform();
    }
    
    while (app.isOpen()) {
        sf::Event event;
        while (app.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                app.close();
            }
        }
        
        frameTime = frameClock.restart();
        
        frameCount += frameTime;
        if (frameCount.asSeconds() > 1.f) {
            frameCount = sf::Time::Zero;
            std::stringstream ss;
            ss << "FPS: " << (1.f / frameTime.asSeconds());
            frameDisplay.setString(ss.str());
        }
        
        animation.update(frameTime);
        
        app.clear();
        
        for (unsigned int i = 0; i < 10000; i++) {            
            app.draw(animation, matrices[i]);
        }
        
        app.draw(frameDisplay);
        
        app.display();
    }
    
    return 0;
}
