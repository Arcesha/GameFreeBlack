#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running;
    int escape_press_count;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif