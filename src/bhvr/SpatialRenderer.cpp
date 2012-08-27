#include <iostream>
#include "attr/Transform.h"
#include "attr/Depth.h"
#include "bhvr/SpatialRenderer.h"

namespace bhvr {

bool SpatialLess::operator()(const std::shared_ptr<SpatialBase> &a,
                             const std::shared_ptr<SpatialBase> &b) const {
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
    for (SpatialMap::iterator iter = mRegistered.begin();
         iter != mRegistered.end(); iter++) {
        SpatialPtr spatial(iter->second(*entity.lock()));
        if (spatial) {
            mSpatials.insert(spatial);
            int sz = mSpatials.size();
            mSources[entity].push_back(spatial);
        }
    }
}

void SpatialRenderer::removedEntity(const da::EntityRef &entity) {
    SpatialSourceMap::iterator search = mSources.find(entity);
    
    for (unsigned int i = 0; i < search->second.size(); i++) {
        mSpatials.erase(search->second[i]);
    }
    
    mSources.erase(entity);
}

void SpatialRenderer::updateEntities(da::EntityGroup &entities) {
    SpatialSet::iterator iter;
    
    for (iter = mSpatials.begin(); iter != mSpatials.end(); iter++) {
        mTarget.draw(**iter);
    }
}

}
