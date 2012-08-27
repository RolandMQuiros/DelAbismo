#include <iostream>

#include <SFML/Window/Event.hpp>

#include "da/Game.h"
#include "da/DAException.h"

namespace da {

Game::Game() :
sf::RenderWindow(sf::VideoMode::getDesktopMode(), "delabismo",
                 sf::Style::Close) {
}

Game::Game(sf::VideoMode mode, const std::string& title,
           unsigned long windowStyle, const sf::ContextSettings& settings) :
sf::RenderWindow(mode, title, windowStyle, settings) {
    
}

void Game::pushState(StatePtr state) {
    if (state) {
        state->initialize();
        mvStates.push_front(state);
    }
}

void Game::pushState(State *state) {
    if (state != NULL) {
        pushState(StatePtr(state));
    }
}

StatePtr Game::popState() {
    StatePtr popped = mvStates.front();
    popped->dispose();
    mvStates.pop_front();
    return popped;
}

void Game::pushBackState(StatePtr state) {
    if (state) {
        state->initialize();
        mvStates.push_back(state);
    }
}

StatePtr Game::popBackState() {
    StatePtr popped = mvStates.back();
    popped->dispose();
    mvStates.pop_back();
    return popped;
}

Game::~Game() {
    while (!mvStates.empty()) {
        mvStates.front()->dispose();
        mvStates.pop_front();
    }
}

sf::Time Game::getFrameTime() const {
    return mvFrameTime;
}

int Game::run() {
    while (isOpen() && !mvStates.empty()) {
        sf::Event event;
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                close();                
            }
        }
        
        if (isOpen()) {
            mvFrameTime = mvFrameClock.restart();
            
            std::deque<StatePtr>::iterator iter;
            for (iter = mvStates.begin(); iter != mvStates.end(); iter++) {
                try {
                    (*iter)->update();
                    if (!mvStates.empty()) {
                        clear();
                        (*iter)->draw();
                        display();
                    }
                } catch (DAException &e) {
                    // If an exception manages to propagate to this level of
                    // operation, we can assume it's pretty severe and we'll
                    // just let ourselves crash.
                    std::cerr << e.message();
                    close();
                    
                    return EXIT_FAILURE;
                }
            }
        }
    }
    
    return EXIT_SUCCESS;
}

}