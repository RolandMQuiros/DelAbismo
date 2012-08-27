#include "attr/Depth.h"
#include "attr/TileLayer.h"
#include "bhvr/TileLayerRenderer.h"

namespace bhvr {

TileLayerRenderer::TileLayerRenderer(DepthDrawList &list) :
DepthRenderer(list),
mCurrentLayer(NULL) {
    
}

bool TileLayerRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<attr::Depth>() &&
           entity.hasAttribute<attr::TileLayer>();
}

void TileLayerRenderer::updateEntity(const sf::Time &deltaTime,
                                     da::Entity &entity) {
    attr::Depth &depth = entity.getAttribute<attr::Depth>();
    attr::TileLayer &layer = entity.getAttribute<attr::TileLayer>();
    
    
}

}
