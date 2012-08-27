#ifndef ATTR_TILELAYER_H
#define ATTR_TILELAYER_H

#include "da/Attribute.h"

namespace attr {

class TileLayer : public da::Attribute<TileLayer> {
public:    
    struct Tile {
        unsigned int id;
        unsigned int tileSet;
    };
    
    std::vector<Tile> mvTiles;
};

}

#endif
