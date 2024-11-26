#include "Player.h" 
#include <iostream> 

using namespace std;

Player::Player(int x, int y, SDL_Renderer* renderer)
    : renderer(renderer) {

    SDL_Surface* tempSurface = SDL_LoadBMP(""); // ��������� ���� ��������, ��� ��� � ������:(
    if (!tempSurface) {
        cerr << "������ �������� �����������: " << SDL_GetError() << std::endl;
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }
}           

void Player::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}
