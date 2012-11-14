#ifndef BHVR_WALKER_H
#define BHVR_WALKER_H

#include <da/EntityBehavior.h>
#include <da/twod/Spatial.h>

namespace bhvr {

/**
 * Sets an Entity's sprite to certain poses depending on its motion.
 */
class Walker : public da::EntityBehavior {
private:
    sf::Time mTime;
    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntity(const da::EntityPtr &entity);
};

}

#endif
