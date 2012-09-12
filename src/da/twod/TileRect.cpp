#include "da/twod/TileRect.h"

namespace da {

TileRect::TileRect(unsigned int widthInTiles, unsigned int heightInTiles,
                   unsigned int tileWidth, unsigned int tileHeight) :
mpWidth(widthInTiles * tileWidth),
mpHeight(heightInTiles * tileHeight),
mpTileWidth(tileWidth),
mpTileHeight(tileHeight),
mpWidthInTiles(widthInTiles),
mpHeightInTiles(heightInTiles),
mpSizeInTiles(widthInTiles * heightInTiles) {

}

TileRect::TileRect(const TileRect &other) :
mpWidth(other.mpWidth),
mpHeight(other.mpHeight),
mpTileWidth(other.mpTileWidth),
mpTileHeight(other.mpTileHeight),
mpWidthInTiles(other.mpWidthInTiles),
mpHeightInTiles(other.mpHeightInTiles),
mpSizeInTiles(other.mpSizeInTiles) {

}

TileRect &TileRect::operator=(const TileRect &other) {
    mpWidth = other.mpWidth;
    mpHeight = other.mpHeight;
    mpTileWidth = other.mpTileWidth;
    mpTileHeight = other.mpTileHeight;
    mpWidthInTiles = other.mpWidthInTiles;
    mpHeightInTiles = other.mpHeightInTiles;
    mpSizeInTiles = other.mpSizeInTiles;
    return *this;
}

void TileRect::redim(unsigned int widthInTiles, unsigned int heightInTiles,
                     unsigned int tileWidth, unsigned int tileHeight) {
    mpWidth = widthInTiles * tileWidth;
    mpHeight = heightInTiles * tileHeight;
    mpTileWidth = tileWidth;
    mpTileHeight = tileHeight;
    mpWidthInTiles = widthInTiles;
    mpHeightInTiles = heightInTiles;
    mpSizeInTiles = widthInTiles * heightInTiles;
}

unsigned int TileRect::getWidth() const {
    return mpWidth;
}

unsigned int TileRect::getHeight() const {
    return mpHeight;
}

unsigned int TileRect::getTileWidth() const {
    return mpTileWidth;
}

unsigned int TileRect::getTileHeight() const {
    return mpTileHeight;
}

unsigned int TileRect::getWidthInTiles() const {
    return mpWidthInTiles;
}

unsigned int TileRect::getHeightInTiles() const {
    return mpHeightInTiles;
}

unsigned int TileRect::getSizeInTiles() const {
    return mpSizeInTiles;
}

unsigned int TileRect::rowColToIndex(unsigned int row, unsigned int col) const {
    return rowColToIndex(row, col, mpWidthInTiles, mpHeightInTiles);
}

void TileRect::indexToRowCol(int index, int &row, int &col) const {
    indexToRowCol(index, mpWidthInTiles, row, col);
}

void TileRect::indexToRowCol(int index, int width, int& row, int& col) {
    row = index / width;
    col = index % width;
}

unsigned int TileRect::rowColToIndex(unsigned int row, unsigned int col,
                                     unsigned int width, unsigned int height) {
    return (row % height) * width + (col % width);
}

}
