#ifndef SPRITESPATIAL_H
#define SPRITESPATIAL_H

#include <SFML/Graphics/RenderTarget.hpp>

#include <da/twod/attr/Transform.h>
#include <da/twod/Spatial.h>

#include "attr/Sprite.h"

class SpriteSpatial : public da::Spatial<SpriteSpatial> {
public:
    static da::SpatialBase *create(da::Entity &entity);
    
    SpriteSpatial(da::Entity &entity);
private:
    da::attr::Transform &mTransform;
    attr::Sprite &mSprite;
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
