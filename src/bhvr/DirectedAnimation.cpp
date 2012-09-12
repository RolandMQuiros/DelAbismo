#include <SFML/Graphics/RenderTarget.hpp>

#include <da/MathHelper.h>
#include <da/twod/attr/Transform.h>

#include "attr/DirectedAnimation.h"
#include "bhvr/DirectedAnimation.h"

namespace bhvr {

DirectedAnimation::Spatial::Spatial(da::Entity &entity) try :
da::Spatial<DirectedAnimation>(entity),
mTransform(entity.getAttribute<da::attr::Transform>()),
mAnimation(entity.getAttribute<attr::DirectedAnimation>()) {
    
} catch (da::DAException &e) {
    throw;
}    

da::SpatialBase *DirectedAnimation::Spatial::create(da::Entity &entity) {    
    if (entity.hasAttribute<attr::DirectedAnimation>() &&
        entity.hasAttribute<da::attr::Transform>()) {
        return new Spatial(entity);
    }
    
    return NULL;
}

void DirectedAnimation::Spatial::draw(sf::RenderTarget &target,
                                      sf::RenderStates states) const {    
    states.transform *= mTransform.getTransform();

    target.draw(mAnimation.animations[mAnimation.index], states);
}

bool DirectedAnimation::isCompatible(const da::Entity &entity) const {
    bool ret = entity.hasAttribute<attr::DirectedAnimation>() &&
               entity.hasAttribute<da::attr::Transform>();
    return ret;
}

void DirectedAnimation::updateEntity(da::Entity &entity) {
    attr::DirectedAnimation &anim =
        entity.getAttribute<attr::DirectedAnimation>();
    
    da::attr::Transform &xform =
        entity.getAttribute<da::attr::Transform>();
    
    if (anim.animations.size() > 0) {  
        anim.index = anim.animations.size() *
            xform.getRotation() / da::MathHelper::ThreeSixty;
        
        anim.animations[anim.index].update(getDelta());
    }
}
    
}
