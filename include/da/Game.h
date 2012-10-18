/* 
 * File:   Game.h
 * Author: rquiros
 *
 * Created on January 7, 2012, 3:52 PM
 */

#ifndef DA_GAME_H
#define	DA_GAME_H

#include <deque>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "da/ContentManager.h"
#include "da/State.h"

namespace da {

class Game : public sf::RenderWindow {
public:
    /**Content management system */
    ContentManager content;
    
    /**Create a Game with default settings*/
    Game();
    /**Creates a Game
     * @param mode
     * @param title
     * @param windowStyle
     * @param settings
     */
    Game(sf::VideoMode mode, const std::string &title,
         unsigned long windowStyle=sf::Style::Close,
         const sf::ContextSettings &settings=sf::ContextSettings());
    
    virtual ~Game();
    
    /**Adds a State to the front of this Game's State list.
     * Adds a State to the front of the State list, and only if the provided
     * reference is valid.
     * @param state pointer to state to push
     */
    void pushState(StatePtr state);
    void pushState(State *state);
    
    /**Removes a State from the front of this Game's State list.
     * @return Reference to the popped State.
     */
    StatePtr popState();
    
    /**Adds a State to the back of this Game's State list.
     * Adds a State to the back of the State list, and only if the provided
     * reference is valid
     * @param state pointer state to push
     */
    void pushBackState(StatePtr state);
    
    /**Removes a State from the back of this Game's State list
     * @return Reference to the popped State
     */
    StatePtr popBackState();
    
    sf::Time getFrameTime() const;
    
    /**Run the game logic
     */
    int run();
private:
    std::deque<StatePtr> mvStates;
    sf::Clock mvFrameClock;
    sf::Time mvFrameTime;
};

}

#endif	/* GAME_H */
