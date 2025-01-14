#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(int x, int y, SDL_Renderer* renderer)
    : renderer(renderer), rect{ x, y, 50, 50 } // �������������� rect � renderer, rect - ������� � ������� ���������
{
    // ��������� ����������� ������
    SDL_Surface* tempSurface = SDL_LoadBMP("player.bmp"); // ������� ���������� ��� �����
    if (!tempSurface) {
        cerr << "������ �������� ����������� ������: " << SDL_GetError() << std::endl;
        texture = nullptr; // ������������� �������� � nullptr ��� ������
        return;  // ������� �� ������������
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface); // ������� ��������
        SDL_FreeSurface(tempSurface); // ����������� �����������
        if (!texture) {
            cerr << "������ �������� �������� ������: " << SDL_GetError() << std::endl;
            texture = nullptr;
        }
    }
    // ���� �������� �� ���� �������, ��������� ���������
    if (!texture) {
        cerr << "�� ������� ��������� ��� ������� �������� ������." << endl;
        exit(EXIT_FAILURE);
    }
}

Player::~Player() {
    if (texture) {
        SDL_DestroyTexture(texture); // ����������� ������� ��������
    }
}

void Player::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &rect); // ������������ ���������
    }
}

void Player::handleInput(const Uint8* state) {
    if (state[SDL_SCANCODE_UP]) {
        rect.y -= SPEED; // �������� �����
    }
    if (state[SDL_SCANCODE_DOWN]) {
        rect.y += SPEED; // �������� ����
    }
    if (state[SDL_SCANCODE_LEFT]) {
        rect.x -= SPEED; // �������� �����
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        rect.x += SPEED; // �������� ������
    }
    // ����������� ����������� ��������� ��������� ������
    rect.x = max(0, min((int)rect.x, 1920 - (int)rect.w));
    rect.y = max(0, min((int)rect.y, 1080 - (int)rect.h));
}

bool Player::hasReachedExit() {
    // �������� �� ���� ������
    return rect.x >= 1500 && rect.y >= 500; // ���������� true, ���� �������� ������ ������
}