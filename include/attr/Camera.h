#ifndef ATTR_CAMERA_H
#define ATTR_CAMERA_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include "da/Attribute.h"

namespace attr {

struct Camera : public da::Attribute {
    static const char *TypeName;
    static const float DefaultSpeed;
    
    sf::RenderTarget &target;
    sf::View view;
    sf::Vector2f destination;
    float speed;
    
    Camera(sf::RenderTarget &target);
};

}

#endif
