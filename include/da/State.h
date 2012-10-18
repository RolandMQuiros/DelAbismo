/* 
 * File:   State.h
 * Author: rquiros
 *
 * Created on January 7, 2012, 4:00 PM
 */

#ifndef DA_STATE_H
#define	DA_STATE_H

#include <memory>

namespace da {

class State {
public:
    virtual ~State() { };
    
    /**Method called when this State is added to the Game
     */
    virtual void initialize() { };
    /**Method called when this State is removed from the Game
     */
    virtual void dispose() { };
    /**Method called every logic frame
     */
    virtual void update() = 0;
    /**Method called every render frame
     */
    virtual void draw() = 0;
};

typedef std::shared_ptr<State> StatePtr;

}

#endif	/* STATE_H */

