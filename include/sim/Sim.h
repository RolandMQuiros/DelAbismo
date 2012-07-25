#ifndef SIM_SIM_H
#define SIM_SIM_H

#include <memory>

#include "da/DepthDrawList.h"
#include "da/Game.h"
#include "da/EntityManager.h"
#include "da/MapReader.h"
#include "da/State.h"
#include "da/TileLayer.h"
#include "da/TileSet.h"

namespace sim {
    
class Sim : public da::State {
public:
    Sim(da::Game &game);
    
    void initialize();
    void dispose();
    
    void update();
    void draw();

protected:
    void loadMap(const std::string &filename);
    void loadEntities(da::MapReader &reader);

private:
    da::Game &mvGame;
    da::EntityManager mvEntities;
    da::DepthDrawList mvDrawList;
    
    std::vector<std::shared_ptr<da::TileSet> > mvTileSets;
    std::vector<std::unique_ptr<da::TileLayer> > mvTileLayers;
    
    da::EntityPtr createCharacter();
    
    void loadTileSets(da::MapReader &reader);
    void loadTileLayers(da::MapReader &reader);
};
typedef std::shared_ptr<Sim> SimPtr;
    
}

#endif
