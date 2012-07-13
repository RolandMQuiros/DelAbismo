#include "da/TileSet.h"

namespace da {

TileSet::TileSet(TexturePtr texture, unsigned int tileWidth,
                 unsigned int tileHeight) try :
TileRect::TileRect(texture->getSize().x / tileWidth,
                   texture->getSize().y / tileHeight, tileWidth, tileHeight),
mvTexture(texture),
mvTileSubrect(0, 0, tileWidth, tileHeight) {
    mvSprite.setTexture(*mvTexture);
} catch (...) {
    throw;
}

TexturePtr TileSet::getTexture() const {
    return mvTexture;
}

void TileSet::drawTile(sf::RenderTarget &dest, sf::RenderStates &states,
                       unsigned int tileIndex, float x, float y,
                       const sf::Color &color) {
    if (tileIndex < getSizeInTiles()) {
        // Retrieve the row and column from the index
        indexToRowCol(tileIndex, mvTileSubrect.top, mvTileSubrect.left);
        
        // Transform it to pixel-scale
        mvTileSubrect.left *= getTileWidth();
        mvTileSubrect.top *= getTileHeight();
        
        // Set up sprite for drawing
        mvSprite.setTextureRect(mvTileSubrect);
        mvSprite.setPosition(x, y);
        mvSprite.setColor(color);
        
        // Draw sprite
        dest.draw(mvSprite, states);
    }
}

void TileSet::drawTile(sf::RenderTarget &dest, sf::RenderStates &states,
                       unsigned int tileIndex, const sf::Vector2f &pos,
                       const sf::Color &color) {
    drawTile(dest, states, tileIndex, pos.x, pos.y, color);
}

}
