#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() : running(false), window(nullptr), renderer(nullptr) {
    SDL_Init(SDL_INIT_VIDEO); // Инициализация подсистемы видео SDL
}

Game::~Game() {
    if (renderer) SDL_DestroyRenderer(renderer); // Освобождение ресурсов рендерера
    if (window) SDL_DestroyWindow(window);       // Освобождение ресурсов окна
    SDL_Quit();                              // Завершение работы SDL
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL не удалось инициализировать! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // Возвращаем false, если инициализация не удалась
    }

    window = SDL_CreateWindow("FreeNigger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);
    // Создание окна SDL

    if (window == nullptr) {
        std::cerr << "Окно не удалось создать! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // Возвращаем false, если окно не создалось
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Создание рендерера SDL с аппаратным ускорением

    if (renderer == nullptr) {
        std::cerr << "Рендерер не удалось создать! SDL_Error: " << SDL_GetError() << std::endl;
        return false; // Возвращаем false, если рендерер не создался
    }

    this->running = true; // Устанавливаем флаг работы игры в true
    return true;         // Возвращаем true, если инициализация прошла успешно
}

void Game::run() {
    SDL_Event e;

    while (this->running) {
        while (SDL_PollEvent(&e)) {
            // Обработка событий
            if (e.type == SDL_QUIT) {
                this->running = false; // Если нажали на крестик окна, завершаем игру
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    this->running = false; // Если нажали ESC, завершаем игру
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Установка черного цвета
        SDL_RenderClear(renderer);                      // Очистка экрана

        SDL_RenderPresent(renderer);                   // Обновление экрана (отображение того, что нарисовали)
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Установка черного цвета
    SDL_RenderClear(renderer);                      // Очистка экрана

    SDL_RenderPresent(renderer);                   // Обновление экрана
}

SDL_Renderer* Game::getRenderer() const {
    return renderer;  // Возвращаем указатель на рендерер
}