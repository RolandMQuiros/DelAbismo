#include <cmath>
#include "da/MathHelper.h"

namespace da {
namespace MathHelper {
    
const float Pi = 3.14159f;
const float TwoPi = 2.f * Pi;
const float PiOverTwo = Pi / 2.f;
const float PiOverFour = Pi / 4.f;
const float PiOverEight = Pi / 8.f;
const float ThreeSixty = 360.f;

float toRadians(float degrees) {
    return degrees * Pi / 180.f;
}

float toDegrees(float radians) {
    return radians * 180.f / Pi;
}

float distance(float x1, float y1, float x2, float y2) {
    float a = (x2 - x1);
    a *= a;
    
    float b = (y2 - y1);
    b *= b;
    
    return sqrt(a + b);
}

float length(float x, float y) {
    return sqrt(x*x + y*y);
}

}
}
