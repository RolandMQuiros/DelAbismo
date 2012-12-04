#include "TileSet.h"

TileSet::TileSet() :
mTileWidth(0),
mTileHeight(0),
mWidth(0),
mHeight(0),
mTileCount(0) {
    
}

TileSet::TileSet(const da::TexturePtr &texture, unsigned int tileWidth,
                 unsigned int tileHeight) :
mTileWidth(0),
mTileHeight(0),
mWidth(0),
mHeight(0),
mTileCount(0) {
    if (texture) {
        mTexture = texture;
        mTileWidth = tileWidth;
        mTileHeight = tileHeight;
        mWidth = mTexture->getSize().x / mTileWidth;
        mHeight = mTexture->getSize().y / mTileHeight;
        mTileCount = mWidth * mHeight;
    }
}

void TileSet::setTexture(const da::TexturePtr &texture) {
    mTexture = texture;
    if (mTexture) {
        resize();
    } else {
        mWidth = mHeight = mTileCount = 0;
    }
}

da::TexturePtr TileSet::getTexture() const {
    return mTexture;
}

void TileSet::setTileSize(unsigned int tileWidth, unsigned int tileHeight) {
    mTileWidth = tileWidth;
    mTileHeight = tileHeight;
    
    resize();
}

unsigned int TileSet::getTileWidth() const {
    return mTileWidth;
}

unsigned int TileSet::getTileHeight() const {
    return mTileHeight;
}

unsigned int TileSet::getWidth() const {
    return mWidth;
}

unsigned int TileSet::getHeight() const {
    return mHeight;
}

unsigned int TileSet::getTileCount() const {
    return mTileCount;
}

void TileSet::resize() {
    if (mTileWidth > 0 && mTileHeight > 0) {
        mWidth = mTexture->getSize().x / mTileWidth;
        mHeight = mTexture->getSize().y / mTileHeight;
        mTileCount = mWidth * mHeight;
    } else {
        mWidth = mHeight = mTileCount = 0;
    }
}


