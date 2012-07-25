#ifndef DA_ATTRIBUTE_TILELAYER_H
#define DA_ATTRIBUTE_TILELAYER_H

#include <memory>
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "da/Attribute.h"
#include "da/TileSet.h"
#include "da/TileRect.h"

namespace da {

class TileLayer : public TileRect,
                  public Attribute,
                  public sf::Drawable {
public:
    static const char *TypeName;
    
    TileLayer();
    TileLayer(unsigned int width, unsigned int height,
              unsigned int tileWidth, unsigned int tileHeight);
    
    void addTileSet(std::shared_ptr<TileSet> tileSet);
    
    void setTileId(unsigned int row, unsigned int col, unsigned int tileId);
    unsigned int getTileId(unsigned int row, unsigned int col);
    
    void setWrap(bool wrap);
    bool getWrap() const;
    
    void setColor(const sf::Color &color);
    const sf::Color &getColor() const;
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
    std::vector<std::shared_ptr<TileSet> > mvTileSets;
    unsigned int mvTileSetIds;
    /** Wrap flag */
    bool mvWrap;
    /** Color*/
    sf::Color mvColor;
};

} // namespace da

#endif
