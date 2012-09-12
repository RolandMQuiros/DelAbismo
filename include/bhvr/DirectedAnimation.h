#ifndef BHVR_DIRECTEDANIMATION_H
#define BHVR_DIRECTEDANIMATION_H

#include <da/EntityBehavior.h>
#include <da/twod/Spatial.h>
#include <da/twod/attr/Transform.h>
#include "attr/DirectedAnimation.h"

namespace bhvr {
    
class DirectedAnimation : public da::EntityBehavior {
public:
    class Spatial : public da::Spatial<DirectedAnimation> {
    public:
        Spatial(da::Entity &entity);
        static da::SpatialBase *create(da::Entity &entity);

    private:
        da::attr::Transform &mTransform;
        attr::DirectedAnimation &mAnimation;
        
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(da::Entity &entity);
};

}

#endif
