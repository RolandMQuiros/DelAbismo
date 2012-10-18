#ifndef DA_TILESET_H
#define DA_TILESET_H

#include <map>
#include <vector>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "da/ContentTypes.h"
#include "da/twod/TileRect.h"

namespace da {

class TileSet : public TileRect {
public:
    /**Create a TileSet
     * @param texture source texture
     * @param tileWidth tile width in pixels
     * @param tileHeight tile height in pixels
     */
    TileSet(da::TexturePtr texture, unsigned int tileWidth,
            unsigned int tileHeight);
    /**Get TileSet source texture
     * @return source texture
     */
    da::TexturePtr getTexture() const;
    /**Draws a tile onto a sf::RenderTarget
     * @param dest RenderTarget to draw onto
     * @param tileIndex index of tile to draw
     * @param x x-position of render
     * @param y y-position of render
     */
    void drawTile(sf::RenderTarget &dest, sf::RenderStates &states,
                  unsigned int tileIndex, float x, float y);
    /**Draws a tile onto a sf::RenderTarget
     * @param dest RenderTarget to draw onto
     * @param tileIndex index of tile to draw
     * @param pos render position
     */
    void drawTile(sf::RenderTarget &dest, sf::RenderStates &states,
                  unsigned int tileIndex, const sf::Vector2f &pos);
private:
    da::TexturePtr mvTexture;
    sf::Sprite mvSprite;
    sf::IntRect mvTileSubrect;
};
typedef std::shared_ptr<TileSet> TileSetPtr;
typedef std::weak_ptr<TileSet> TileSetRef;

}

#endif
