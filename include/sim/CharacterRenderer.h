#ifndef SIM_CHARACTERRENDERER_H
#define SIM_CHARACTERRENDERER_H

#include <vector>
#include "da/Depth.h"
#include "da/DepthRenderBehavior.h"

namespace sim {

class CharacterRenderer : public da::DepthRenderBehavior {
private:
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const sf::Time &deltaTime, da::Entity &entity);
};

}

#endif
