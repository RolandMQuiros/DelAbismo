#include "da/Game.h"

int main(int argc, char *argv[]) {
    da::Game game(sf::VideoMode(640, 480), "Del Abismo");
    
    game.setFramerateLimit(60);
    
    return game.run();
}
