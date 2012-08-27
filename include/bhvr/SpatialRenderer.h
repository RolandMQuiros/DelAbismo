#ifndef BHVR_SPATIALRENDERER_H
#define BHVR_SPATIALRENDERER_H

#include <functional>
#include <map>
#include <set>

#include <SFML/Graphics/RenderTarget.hpp>

#include "da/Behavior.h"
#include "Spatial.h"

namespace bhvr {

typedef std::function<SpatialBase *(da::Entity &e)> SpatialCreationFn;

struct SpatialLess {
    bool operator()(const std::shared_ptr<SpatialBase> &a,
                    const std::shared_ptr<SpatialBase> &b) const;
};

class SpatialRenderer : public da::Behavior {
protected:
    bool isCompatible(const da::Entity &entity) const;

    void addedEntity(const da::EntityRef &entity);
    void removedEntity(const da::EntityRef &entity);
    
    void updateEntities(da::EntityGroup &entities);

private:
    typedef std::shared_ptr<SpatialBase> SpatialPtr;
    
    typedef std::map<unsigned int, SpatialCreationFn> SpatialMap;
    typedef std::map<da::EntityRef,
                     std::vector<SpatialPtr>,
                     std::owner_less<da::EntityRef> > SpatialSourceMap;
    typedef std::set<SpatialPtr, SpatialLess> SpatialSet;
    
    sf::RenderTarget &mTarget;
    SpatialMap mRegistered;
    SpatialSourceMap mSources;
    SpatialSet mSpatials;

public:
    SpatialRenderer(sf::RenderTarget &target);
    
    template <class Spatial> void registerSpatial() {
        SpatialMap::iterator search = mRegistered.find(Spatial::typeId());
        
        if (search == mRegistered.end()) {
            mRegistered[Spatial::typeId()] = Spatial::create;
        }
    }

};

}

#endif
