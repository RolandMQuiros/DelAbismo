#ifndef BHVR_TILELAYERRENDERER_H
#define BHVR_TILELAYERRENDERER_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "da/ContentTypes.h"
#include "attr/TileLayer.h"
#include "bhvr/DepthRenderer.h"

namespace bhvr {

class TileLayerRenderer : public DepthRenderer {
public:
    TileLayerRenderer(DepthDrawList &list);
    void addTileSet(const da::TexturePtr &texture, unsigned int tileWidth,
                    unsigned int tileHeight);

protected:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &deltaTime, da::Entity &entity);

private:
    struct TileSet {
        da::TexturePtr texture;
        unsigned int tileWidth;
        unsigned int tileHeight;
        unsigned int tileCount;
    };
    
    /* Replace this with lambdas later */
    attr::TileLayer *mCurrentLayer;
    void drawCurrentLayer(const sf::RenderTarget &target,
                          sf::RenderStates states) const;

    std::vector<TileSet> mTileSets;
    sf::Sprite mStamp;
    
};

}

#endif
