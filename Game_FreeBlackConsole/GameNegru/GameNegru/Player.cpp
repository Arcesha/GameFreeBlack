#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(int x, int y, SDL_Renderer* renderer)
    : renderer(renderer), rect{ x, y, 50, 50 } // Инициализируем rect и renderer, rect - размеры и позиция персонажа
{
    // Загружаем изображение игрока
    SDL_Surface* tempSurface = SDL_LoadBMP("player.bmp"); // Укажите правильное имя файла
    if (!tempSurface) {
        cerr << "Ошибка загрузки изображения игрока: " << SDL_GetError() << std::endl;
        texture = nullptr; // Устанавливаем текстуру в nullptr при ошибке
        return;  // Выходим из конструктора
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface); // Создаем текстуру
        SDL_FreeSurface(tempSurface); // Освобождаем поверхность
        if (!texture) {
            cerr << "Ошибка создания текстуры игрока: " << SDL_GetError() << std::endl;
            texture = nullptr;
        }
    }
    // Если текстура не была создана, завершаем программу
    if (!texture) {
        cerr << "Не удалось загрузить или создать текстуру игрока." << endl;
        exit(EXIT_FAILURE);
    }
}

Player::~Player() {
    if (texture) {
        SDL_DestroyTexture(texture); // Освобождаем ресурсы текстуры
    }
}

void Player::draw(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &rect); // Отрисовываем персонажа
    }
}

void Player::handleInput(const Uint8* state) {
    if (state[SDL_SCANCODE_UP]) {
        rect.y -= SPEED; // Движение вверх
    }
    if (state[SDL_SCANCODE_DOWN]) {
        rect.y += SPEED; // Движение вниз
    }
    if (state[SDL_SCANCODE_LEFT]) {
        rect.x -= SPEED; // Движение влево
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        rect.x += SPEED; // Движение вправо
    }
    // Ограничение перемещения персонажа границами экрана
    rect.x = max(0, min((int)rect.x, 1920 - (int)rect.w));
    rect.y = max(0, min((int)rect.y, 1080 - (int)rect.h));
}

bool Player::hasReachedExit() {
    // Замените на свою логику
    return rect.x >= 1500 && rect.y >= 500; // Возвращаем true, если персонаж достиг выхода
}