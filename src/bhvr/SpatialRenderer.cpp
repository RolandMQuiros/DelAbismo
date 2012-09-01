#include <algorithm>
#include "attr/Transform.h"
#include "attr/Depth.h"
#include "bhvr/SpatialRenderer.h"

namespace bhvr {

bool spatialLess(const std::shared_ptr<SpatialBase> &a,
                 const std::shared_ptr<SpatialBase> &b) {
    if (a && b) {
        attr::Depth &depthA = a->getEntity().getAttribute<attr::Depth>();
        attr::Depth &depthB = b->getEntity().getAttribute<attr::Depth>();
        
        return depthA < depthB;
    }
    return false;
}

SpatialRenderer::SpatialRenderer(sf::RenderTarget &target) :
mTarget(target) {
    
}

bool SpatialRenderer::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<attr::Transform>() &&
           entity.hasAttribute<attr::Depth>();
}

void SpatialRenderer::addedEntity(const da::EntityRef &entity) {
    for (SpatialCreationMap::iterator iter = mRegistered.begin();
         iter != mRegistered.end(); iter++) {
        SpatialPtr spatial(iter->second(*entity.lock()));
        if (spatial) {
            mSpatials.push_back(spatial);
        }
    }
}

void SpatialRenderer::removedEntity(const da::EntityRef &entity) {
    da::EntityPtr entPtr = entity.lock();
    
    for (unsigned int i = 0; i < mSpatials.size(); i++) {
        if (mSpatials[i] && &mSpatials[i]->getEntity() == entPtr.get()) {
            mSpatials.erase(mSpatials.begin() + i--);
        }
    }
}

void SpatialRenderer::updateEntities(da::EntityGroup &entities) {
    std::sort(mSpatials.begin(), mSpatials.end(), spatialLess);
    
    for (unsigned int i = 0; i < mSpatials.size(); i++) {
        mTarget.draw(*mSpatials[i]);
    }
}

}
