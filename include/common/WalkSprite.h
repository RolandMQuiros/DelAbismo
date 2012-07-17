#ifndef COMMON_WALKSPRITE_H
#define COMMON_WALKSPRITE_H

#include <SFML/System/Vector2.hpp>

#include "da/ContentTypes.h"
#include "da/Animation.h"
#include "da/Attribute.h"
#include "da/MathHelper.h"

namespace common {
    
class WalkSprite : public da::Attribute {
public:
    static const char *TypeName;
    static const unsigned int DirectionCount;
    
    enum Direction {
        South = 0,
        SouthEast = 1,
        East = 2,
        NorthEast = 3,
        North = 4,
        NorthWest = 5,
        West = 6,
        SouthWest = 7
    };
    
    da::Animation directions[8];
    
    sf::Vector2f previousPosition;
    
    WalkSprite(const da::TexturePtr &texture, const sf::Vector2i &offset,
               const sf::Vector2i &frameSize, unsigned int framesPerDirection);
};

}

#endif
