#ifndef BHVR_POSES_H
#define BHVR_POSES_H

#include <da/Behavior.h>

namespace bhvr {

class Poses : public da::EntityBehavior {
private:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(da::Entity &entity);
    
};

}

#endif
