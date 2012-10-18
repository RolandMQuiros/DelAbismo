#include <da/twod/attr/Transform.h>
#include <da/twod/attr/Depth.h>
#include "attr/Poses.h"
#include "attr/Sprite.h"

#include "bhvr/Poses.h"

namespace bhvr {

bool Poses::isCompatible(const da::Entity &entity) const {
    return entity.hasAttribute<da::attr::Transform>() &&
           entity.hasAttribute<da::attr::Depth>() &&
           entity.hasAttribute<attr::Poses>() &&
           entity.hasAttribute<attr::Sprite>();
}

void Poses::updateEntity(da::Entity &entity) {
    da::attr::Transform &xform = entity.getAttribute<da::attr::Transform>();
    da::attr::Depth &depth = entity.getAttribute<da::attr::Depth>();
    attr::Poses &poses = entity.getAttribute<attr::Poses>();
    attr::Sprite &sprite = entity.getAttribute<attr::Sprite>();
    
    
}

}
