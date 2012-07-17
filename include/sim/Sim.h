#ifndef SIM_SIM_H
#define SIM_SIM_H

#include <memory>

#include "da/DepthDrawList.h"
#include "da/Game.h"
#include "da/EntityManager.h"
#include "da/State.h"

namespace sim {
    
class Sim : public da::State {
public:
    Sim(da::Game &game);
    
    void initialize();
    void dispose();
    
    void update();
    void draw();
    
private:
    da::Game &mvGame;
    da::EntityManager mvEntities;
    da::DepthDrawList mvDrawList;
};
typedef std::shared_ptr<Sim> SimPtr;
    
}

#endif
