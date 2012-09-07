#include <sstream>
#include <iostream>
#include <gtest/gtest.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "rapidxml/rapidxml.hpp"

#include "da/StringHelper.h"

// FUCK
#define private public

#include "marked/KeyboardInput.h"

namespace test {    
    TEST(KeyboardTest, PressTests) {
        sf::RenderWindow app(sf::VideoMode(160, 120), "Keyboard Test");
        sf::Clock frameClock;
        sf::Text display;
        display.setCharacterSize(10);
        
        // Create Input.  Break dependency on rapidxml?
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<> *node;
        
        std::string xmlText = da::StringHelper::getFileText("KeyboardTestXml.xml");
        
        std::cout << xmlText << std::endl;
        
        doc.parse<0>((char*)xmlText.c_str());
        node = doc.first_node();
        
        marked::KeyboardInput input(node);
        
        while (app.isOpen()) {
            sf::Event event;
            while (app.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    app.close();
                }
            }
            
            input.update();
            
            app.clear();
            
            // Put the button bitstrings into char strings
            std::stringstream ss;
            {                
                ss << "Pressed: ";
                
                for (unsigned int i = 0; i < marked::Input::ActionCount; i++) {
                    ss << ((input.mPressed >> i) & 1);
                }
                ss << std::endl;
                
                ss << "Released: ";
                for (unsigned int i = 0; i < marked::Input::ActionCount; i++) {
                    ss << ((input.mReleased >> i) & 1);
                }
                ss << std::endl;
                
                ss << "Held: ";
                for (unsigned int i = 0; i < marked::Input::ActionCount; i++) {
                    ss << ((input.mHeld >> i) & 1);
                }
                ss << std::endl;
            }
            
            ss << "FPS: " << (1.f / frameClock.restart().asSeconds());
            
            display.setString(ss.str());
            app.draw(display);
            app.display();
        }
    }
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
