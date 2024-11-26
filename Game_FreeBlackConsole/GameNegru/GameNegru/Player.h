#ifndef PLAYER_H 
#define PLAYER_H 

#include <SDL.h> 


const int SPEED = 1;

class Player {
public:
    Player(int x, int y, SDL_Renderer* renderer);
    void handleInput(const Uint8* state);
    void draw(SDL_Renderer* renderer);
    bool hasReachedExit();

private:
    SDL_Rect rect;
    SDL_Texture* texture;                                                  
    SDL_Renderer* renderer;
};

#endif
