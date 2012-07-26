#include "attr/Camera.h"

namespace attr {

const char *Camera::TypeName = "attr::Camera";
const float Camera::DefaultSpeed = 10.f;

Camera::Camera(sf::RenderTarget &target) :
da::Attribute(TypeName),
target(target),
speed(DefaultSpeed) {
    
}

}
