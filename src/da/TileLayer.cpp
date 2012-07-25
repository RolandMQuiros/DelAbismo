#include <cmath>
#include "da/TileLayer.h"

namespace da {

const char *TileLayer::TypeName = "da::TileLayer";

TileLayer::TileLayer(unsigned int widthInTiles, unsigned int heightInTiles,
                     unsigned int tileWidth, unsigned int tileHeight) :
TileRect(widthInTiles, heightInTiles, tileWidth, tileHeight),
Attribute(TypeName),
mvTiles(mpSizeInTiles),
mvTileSetIds(0),
mvWrap(false) {
    
}

void TileLayer::addTileSet(std::shared_ptr<TileSet> tileSet) {
    mvTileSets.push_back(tileSet);
    mvTileSetIds += tileSet->getSizeInTiles();
}

void TileLayer::setTileId(unsigned int row, unsigned int col,
                          unsigned int tileId) {
    unsigned int pos = rowColToIndex(row, col);
    if (pos < getSizeInTiles()) {
        Tile t;
        t.index = tileId;

        for (t.tileSet = 0;
             t.tileSet < mvTileSets.size() &&
                 t.index > mvTileSets.at(t.tileSet)->getSizeInTiles();
             t.tileSet++) {
            t.index -= mvTileSets.at(t.tileSet)->getSizeInTiles();
        }

        mvTiles.at(pos) = t;
    }
}

unsigned int TileLayer::getTileId(unsigned int row, unsigned int col) {
    unsigned int pos = rowColToIndex(row, col);
    if (pos < mvTileSetIds) {
        unsigned int ret = 0;
        Tile t = mvTiles.at(pos);

        for (unsigned int i = 0; i < t.tileSet; i++) {
            ret += mvTileSets.at(i)->getSizeInTiles();
        }

        ret += t.index;

        return ret;
    }
    return 0;
}

void TileLayer::setWrap(bool wrap) {
    mvWrap = wrap;
}

bool TileLayer::getWrap() const {
    return mvWrap;
}

void TileLayer::setColor(const sf::Color &color) {
    mvColor = color;
}

const sf::Color &TileLayer::getColor() const {
    return mvColor;
}

void TileLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::View view(target.getView());
    float dim = sqrt(view.getSize().x * view.getSize().x +
                     view.getSize().y*view.getSize().y);
    sf::FloatRect limit(view.getCenter().x - (dim / 2.f),
                        view.getCenter().y - (dim / 2.f),
                        dim, dim);
    
    float right = limit.left + limit.width;
    float bottom = limit.top + limit.height;

    for (int i = limit.left/getTileWidth()-1; i < right/getTileWidth()+1; i++) {
        for (int j = limit.top/getTileHeight()-1; j < bottom/getTileHeight()+1;
             j++) {
            
            if (mvWrap || (i >= 0 && i < getWidthInTiles() &&
                           j >= 0 && j < getHeightInTiles())) {
                unsigned int pos = rowColToIndex(j, i);
                Tile tile = mvTiles[pos % mvTiles.size()];
                
                if (tile.index > 0) {// && tile.index < getSizeInTiles()) {
                    mvTileSets[tile.tileSet]->drawTile(
                        target, states, tile.index-1, i * (int)getTileWidth(),
                        j * (int)getTileHeight(), mvColor
                    );
                }
            }
        }
    }
}

} // namespace da
