#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (game.init()) {
        game.run();
    }
    else {
        std::cerr << "Game initialization failed." << std::endl;
        return 1;
    }

    return 0;
}