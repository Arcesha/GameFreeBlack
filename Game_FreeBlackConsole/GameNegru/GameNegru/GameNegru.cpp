#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }
    SDL_Quit();
    return 0;
}