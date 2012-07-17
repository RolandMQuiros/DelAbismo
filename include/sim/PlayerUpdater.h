#ifndef SIM_PLAYERUPDATER_H
#define SIM_PLAYERUPDATER_H

#include "da/Behavior.h"

namespace sim {

class PlayerUpdater : public da::Behavior {
public:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &deltaTime, da::Entity &entity);
};

}

#endif
