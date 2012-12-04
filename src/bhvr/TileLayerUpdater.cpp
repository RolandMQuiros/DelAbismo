#include <da/MathHelper.h>
#include "attr/TileLayer.h"
#include "bhvr/TileLayerUpdater.h"

namespace bhvr {

TileLayerUpdater::TileLayerUpdater(sf::RenderTarget &target) :
mTarget(target) {
}

bool TileLayerUpdater::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<attr::TileLayer>();
}

void TileLayerUpdater::beginUpdate(da::EntityGroup &entities) {
    const sf::View &view = mTarget.getView();
    
    // Set up transformation matrix
    sf::Transform transform;
    transform.rotate(view.getRotation(), view.getCenter());
    transform.translate(view.getCenter());
    
    // Create a rectangle the same size as the view, centered at the origin
    mViewRect = sf::FloatRect(-view.getSize().x / 2.f,
                              -view.getSize().y / 2.f,
                              view.getSize().x, view.getSize().y);
    
    // Transform the rect.  sf::Transform only supports axis-aligned rectangles,
    // so we get the bounding box of the rotated rectangle here.  Fortunately,
    // that's precisely what we want.
    mViewRect = transform.transformRect(mViewRect);
    
    // We'll use mViewRect to determine which tiles in an attr::TileLayer to
    // draw.
}

void TileLayerUpdater::updateEntity(const da::EntityPtr &entity) {
    attr::TileLayer &tileLayer = entity->getAttribute<attr::TileLayer>();
    
    // Create a rectangle representing which tiles to draw, using mViewRect and
    // the tile dimensions of each layer
    tileLayer._viewBounds = sf::IntRect(
        (mViewRect.left / tileLayer.tileWidth + 0.5f),
        (mViewRect.top / tileLayer.tileHeight + 0.5f),
        (mViewRect.width / tileLayer.tileWidth + 0.5f),
        (mViewRect.height / tileLayer.tileHeight + 0.5f)
    );
}
    
}
