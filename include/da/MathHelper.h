#ifndef DA_MATHHELPER_H
#define DA_MATHHELPER_H

namespace da {
namespace MathHelper {
    extern const float Pi;
    extern const float TwoPi;
    extern const float PiOverTwo;
    extern const float PiOverFour;
    extern const float PiOverEight;
    extern const float ThreeSixty;
    
    float toRadians(float degrees);
    float toDegrees(float radians);
    
    float distance(float x1, float y1, float x2, float y2);
    float length(float x, float y);
}
}

#endif
