#include "CardinalDirection.h"

float directionToRadians(CardinalDirection direction) {
    switch (direction) {
        case East:
            return 0.f;
        case SouthEast:
            return 0.785982f;
        case South:
            return 1.570796f;
        case SouthWest:
            return 2.356194f;
        case West:
            return 3.141593f;
        case NorthWest:
            return 3.926991f;
        case North:
            return 4.712389f;
        case NorthEast:
            return 5.497787f;
        default:
            return -1.f;
    }
}

int directionToDegrees(CardinalDirection direction) {
    switch (direction) {
        case East:
            return 0;
        case SouthEast:
            return 45;
        case South:
            return 90;
        case SouthWest:
            return 135;
        case West:
            return 180;
        case NorthWest:
            return 225;
        case North:
            return 270;
        case NorthEast:
            return 315;
        default:
            return -1.f;
    }
}

std::string directionToString(CardinalDirection direction) {
    switch (direction) {
        case East:
            return "east";
        case SouthEast:
            return "southeast";
        case South:
            return "south";
        case SouthWest:
            return "southwest";
        case West:
            return "west";
        case NorthWest:
            return "northwest";
        case North:
            return "north";
        case NorthEast:
            return "northeast";
        default:
            return "";
    }
}
