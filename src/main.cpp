#include "da/Game.h"

int main(int argc, char *argv[]) {
    da::Game game(sf::VideoMode(640, 480), "Del Abismo");
    
    return game.run();
}
