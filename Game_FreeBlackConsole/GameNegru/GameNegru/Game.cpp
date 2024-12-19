#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : running(false), window(nullptr), renderer(nullptr) {
    SDL_Init(SDL_INIT_VIDEO); // ������������� ���������� ����� SDL
}

Game::~Game() {
    if (renderer) SDL_DestroyRenderer(renderer); // ������������ �������� ���������
    if (window) SDL_DestroyWindow(window);       // ������������ �������� ����
    SDL_Quit();                              // ���������� ������ SDL
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL �� ������� ����������������! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // ���������� false, ���� ������������� �� �������
    }

    window = SDL_CreateWindow("FreeNigger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    // �������� ���� SDL

    if (window == nullptr) {
        std::cerr << "���� �� ������� �������! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // ���������� false, ���� ���� �� ���������
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // �������� ��������� SDL � ���������� ����������

    if (renderer == nullptr) {
        std::cerr << "�������� �� ������� �������! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // ���������� false, ���� �������� �� ��������
    }

    this->running = true; // ������������� ���� ������ ���� � true
    return true;         // ���������� true, ���� ������������� ������ �������
}

void Game::run() {
    SDL_Event e;

    while (this->running) {
        while (SDL_PollEvent(&e)) {
            // ��������� �������
            if (e.type == SDL_QUIT) {
                this->running = false; // ���� ������ �� ������� ����, ��������� ����
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    this->running = false; // ���� ������ ESC, ��������� ����
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ��������� ������� �����
        SDL_RenderClear(renderer);                      // ������� ������

        SDL_RenderPresent(renderer);                   // ���������� ������ (����������� ����, ��� ����������)
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ��������� ������� �����
    SDL_RenderClear(renderer);                      // ������� ������

    SDL_RenderPresent(renderer);                   // ���������� ������
}

SDL_Renderer* Game::getRenderer() const {
    return renderer;  // ���������� ��������� �� ��������
}