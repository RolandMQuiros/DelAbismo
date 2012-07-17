#ifndef SIM_PLAYERRENDERER_H
#define SIM_PLAYERRENDERER_H

#include "da/RenderBehavior.h"

namespace sim {

class PlayerRenderer : public da::RenderBehavior {
protected:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &deltaTime, da::Entity &entity);
};

}

#endif
