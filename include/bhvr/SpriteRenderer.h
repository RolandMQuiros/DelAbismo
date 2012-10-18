#ifndef BHVR_SPRITERENDERER_H
#define BHVR_SPRITERENDERER_H

#include <SFML/Graphics/RenderTarget.hpp>

#include <da/Behavior.h>
#include <da/twod/Spatial.h>

#include "da/twod/attr/Transform.h"
#include "attr/Sprite.h"

namespace bhvr {

class SpriteRenderer : public da::Behavior {
public:
    
    class Spatial : public da::Spatial<Spatial> {
    public:
        static da::SpatialBase *create(da::Entity &entity);
        
        Spatial(da::Entity &entity);
    private:
        da::attr::Transform &mTransform;
        attr::Sprite &mSprite;
        
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

private:
    
    bool isCompatible(const da::Entity &entity) const;
    void updateEntities(da::EntityGroup &entities);
};
    
}

#endif
