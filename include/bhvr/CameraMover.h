#ifndef BHVR_CAMERAMOVER_H
#define BHVR_CAMERAMOVER_H

#include "da/Behavior.h"

namespace bhvr {

class CameraMover : public da::Behavior {
protected:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &deltaTime, da::Entity &entity);
};

}

#endif