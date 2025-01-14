#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, const std::string& text, const std::string& imagePath)
    : text(text), clicked(false) // Конструктор класса Button, инициализация полей
{
    rect.x = x;    // Координата X кнопки
    rect.y = y;    // Координата Y кнопки
    rect.w = width; // Ширина кнопки
    rect.h = height; // Высота кнопки

    texture = nullptr; // Изначально текстура не задана
    if (!imagePath.empty()) {
        // Если путь к изображению не пустой
        SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str()); // Загружаем изображение
        if (!surface) {
            std::cerr << "Не удалось загрузить изображение: " << imagePath << " SDL_Error: " << SDL_GetError() << std::endl;
            return; // Если загрузка не удалась, выходим из конструктора
        }
        texture = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), surface);
        // Создаем текстуру из загруженного изображения
        SDL_FreeSurface(surface); // Осв02обождаем поверхность после создания текстуры
        if (!texture) {
            std::cerr << "Не удалось создать текстуру из поверхности SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}

Button::~Button() {
    if (texture) {
        SDL_DestroyTexture(texture); // Освобождение ресурсов текстуры
    }
}

void Button::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        // Если текстура есть, отрисовываем ее
    }
    else {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Устанавливаем серый цвет кнопки
        SDL_RenderFillRect(renderer, &rect);                 // Рисуем прямоугольник
    }
}

bool Button::isClicked(int mouseX, int mouseY) {
    if (mouseX > rect.x && mouseX < rect.x + rect.w &&
        mouseY > rect.y && mouseY < rect.y + rect.h) {
        // Проверяем, попадает ли клик в область кнопки
        return true; // Возвращаем true, если клик попал
    }
    return false; // Возвращаем false, если клик не попал
}

const std::string& Button::getText() const {
    return text; // Возвращаем текст кнопки
}

void Button::setClicked(bool isClicked) {
    this->clicked = isClicked; // Устанавливаем флаг нажатия кнопки
}

bool Button::getClicked() const {
    return clicked; // Возвращаем флаг нажатия кнопки
}