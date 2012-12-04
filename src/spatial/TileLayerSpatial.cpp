#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>

#include <da/MathHelper.h>
#include "spatial/TileLayerSpatial.h"

da::SpatialBase *TileLayerSpatial::create(da::Entity &entity) {
    if (entity.hasAttribute<attr::TileLayer>()) {
        return new TileLayerSpatial(entity);
    }
    
    return NULL;
}

TileLayerSpatial::TileLayerSpatial(da::Entity &entity) :
da::Spatial<TileLayerSpatial>(entity),
mLayer(entity.getAttribute<attr::TileLayer>()) {    
    // Get the lower and upper ID numbers for each tile set
    unsigned lower = 1;
    for (unsigned int i = 0; i < attr::TileLayer::sTileSets.size(); i++) {
        std::pair<unsigned int, unsigned int> bounds;
        da::TexturePtr &texture = attr::TileLayer::sTileSets[i];
        
        sf::Vector2i size;
        size.x = texture->getSize().x / mLayer.tileWidth;
        size.y = texture->getSize().y / mLayer.tileHeight;
        unsigned int area = size.x * size.y;
        
        mTotalChips += area;
        
        bounds.first = lower;
        bounds.second = lower + area - 1;
        
        lower = bounds.second + 1;
        
        mTileSetBounds.push_back(bounds);
        mTileSetWidths.push_back(size.x);
    }
}

void TileLayerSpatial::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::IntRect &bounds = mLayer._viewBounds;
    sf::Sprite sprite;
    
    unsigned int bottom = bounds.top + bounds.height;
    unsigned int right = bounds.left + bounds.width;
    
    unsigned int lowerRow = std::max(bounds.top, 0);
    unsigned int upperRow = std::min(bottom, mLayer.height);
    
    unsigned int lowerCol = std::max(bounds.left, 0);
    unsigned int upperCol = std::min(right, mLayer.width);
    
    for (unsigned int j = lowerRow; j < upperRow; j++) {
        for (unsigned int i = lowerCol; i < upperCol; i++) {
            // Calculate the tile index of the current row/column
            unsigned int tile = i + (j * mLayer.width);
            unsigned int id;
            
            // Skip blank tiles
            if ((id = mLayer.tileIds[tile]) == 0) {
                continue;
            }
            
            // Find which tileset the tile id belongs to
            int tileset = searchTileSets(id);
            if (tileset < 0) {
                continue;
            }
            
            // Find the tile subrect in the tileset texture
            id -= mTileSetBounds[tileset].first;
            unsigned int tileSetWidth = mTileSetWidths[tileset];
            sf::IntRect tileRect((id % tileSetWidth) * mLayer.tileWidth,
                                 (id / tileSetWidth) * mLayer.tileHeight,
                                 mLayer.tileWidth, mLayer.tileHeight);
            
            // Calculate the draw position
            sf::Vector2f pos(i * mLayer.tileWidth, j * mLayer.tileHeight);
            
            // Apply current tile to sprite
            sprite.setTexture(*attr::TileLayer::sTileSets[tileset]);
            sprite.setTextureRect(tileRect);
            sprite.setPosition(pos);
            
            // Draw the tile
            target.draw(sprite);
        }
    }
}

int TileLayerSpatial::searchTileSets(unsigned int id) const {
    // Error if the id is greater than the number of chips available
    if (id >= mTotalChips + 1) {
        return -1;
    }
    
    // Check the middle set first
    unsigned int idx = mTileSetBounds.size() >> 1;
    
    while (idx < mTileSetBounds.size()) {
        const std::pair<unsigned int, unsigned int> &midBounds =
                mTileSetBounds[idx];
        
        // Check the greater or lesser sets
        if (id > midBounds.second) {
            idx++;
        } else if (id < midBounds.first) {
            idx--;
        } else {
            return idx;
        }
    }
    
    // No tileset found.
    return -1;
}
