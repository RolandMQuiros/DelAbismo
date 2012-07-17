#include "da/Game.h"
#include "sim/Sim.h"

int main(int argc, char *argv[]) {
    da::Game game(sf::VideoMode(640, 480), "Del Abismo");
    
    game.setFramerateLimit(60);
    
    sim::SimPtr sim(new sim::Sim(game));
    game.pushState(sim);
    
    return game.run();
}
