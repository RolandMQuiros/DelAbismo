#include <functional>
#include "attr/Camera.h"

namespace attr {

const float Camera::DefaultSpeed = 10.f;

Camera::Camera(sf::RenderTarget &target) :
target(target),
speed(DefaultSpeed) {
    
}

}
