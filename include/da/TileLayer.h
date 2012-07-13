#ifndef DA_ATTRIBUTE_TILELAYER_H
#define DA_ATTRIBUTE_TILELAYER_H

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "da/TileSet.h"
#include "da/TileRect.h"

namespace da {

class TileLayer : public da::TileRect,
                  public sf::Drawable,
                  public sf::Transformable {
public:    
    TileLayer();
    TileLayer(unsigned int width, unsigned int height,
              unsigned int tileWidth, unsigned int tileHeight);
    
    void addTileSet(TileSetPtr tileSet);
    
    void setTileId(unsigned int row, unsigned int col, unsigned int tileId);
    unsigned int getTileId(unsigned int row, unsigned int col);
    
    void setWrap(bool wrap);
    bool getWrap() const;
    
    void setScroll(sf::Vector2f const &scroll);
    const sf::Vector2f &getScroll() const;
    
    void setColor(const sf::Color &color);
    const sf::Color &getColor() const;
    
    void update(const sf::Time &time);
protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
private:
    struct Tile {
        unsigned int index;
        unsigned int tileSet;
    };
    /** Tile data */
    std::vector<Tile> mvTiles;
    /** TileSet data */
    std::vector<TileSetPtr> mvTileSets;
    unsigned int mvTileSetIds;
    /** Wrap flag */
    bool mvWrap;
    /** Layer scrolling */
    sf::Vector2f mvScroll;
    /** Color*/
    sf::Color mvColor;
};
typedef std::shared_ptr<TileLayer> TileLayerPtr;

} // namespace da

#endif
