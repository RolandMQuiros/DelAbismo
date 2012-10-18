#ifndef SPATIAL_SPRITE_H
#define SPATIAL_SPRITE_H

#include <SFML/Graphics/RenderTarget.hpp>

#include <da/twod/attr/Transform.h>
#include <da/twod/Spatial.h>

#include "attr/Sprite.h"

namespace spatial {

class Sprite : public da::Spatial<Sprite> {
public:
    static da::SpatialBase *create(da::Entity &entity);
    
    Sprite(da::Entity &entity);
private:
    da::attr::Transform &mTransform;
    attr::Sprite &mSprite;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

}

#endif
