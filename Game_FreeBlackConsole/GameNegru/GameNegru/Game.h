#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();
    void render();
    SDL_Renderer* getRenderer() const; // �������� ������ ��� ���������

    bool running;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif