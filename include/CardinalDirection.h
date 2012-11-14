#ifndef CARDINALDIRECTION_H
#define CARDINALDIRECTION_H

#include <string>

enum CardinalDirection {
    East = 0,
    SouthEast = 1,
    South = 2,
    SouthWest = 3,
    West = 4,
    NorthWest = 5,
    North = 6,
    NorthEast = 7,
    DirectionCount = 8
};

float directionToRadians(CardinalDirection direction);
int directionToDegrees(CardinalDirection direction);
std::string directionToString(CardinalDirection direction);

#endif
