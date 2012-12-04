#ifndef TILELAYERSPATIAL_H
#define TILELAYERSPATIAL_H

#include <SFML/Graphics/Sprite.hpp>

#include <da/EntityBehavior.h>
#include <da/twod/Spatial.h>

#include "attr/TileLayer.h"

class TileLayerSpatial : public da::Spatial<TileLayerSpatial> {
public:
    static da::SpatialBase *create(da::Entity &entity);
    TileLayerSpatial(da::Entity &entity);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    attr::TileLayer &mLayer;
    std::vector<std::pair<unsigned int, unsigned int>> mTileSetBounds;
    unsigned int mTotalChips;
    
    std::vector<unsigned int> mTileSetWidths;
    
    int searchTileSets(unsigned int id) const;
};

#endif
