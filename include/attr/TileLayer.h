#ifndef ATTR_TILELAYER_H
#define ATTR_TILELAYER_H

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <da/Attribute.h>
#include <da/ContentTypes.h>

namespace attr {

struct TileLayer : public da::Attribute<TileLayer> {
    static std::vector<da::TexturePtr> sTileSets;
    
    bool isWrap;
    
    unsigned int width;
    unsigned int height;
    
    unsigned int tileWidth;
    unsigned int tileHeight;
    
    std::vector<unsigned int> tileIds;
    
    /** Internal.  Sets which tiles are visible onscreen. */
    sf::IntRect _viewBounds;
};

}

#endif
