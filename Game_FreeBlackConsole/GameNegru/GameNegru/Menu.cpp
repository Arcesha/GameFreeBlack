#include "Menu.h"
#include <iostream>

Menu::Menu() {
    // Конструктор класса Menu
}

Menu::~Menu() {
    // Деструктор класса Menu
}

void Menu::addButton(Button button) {
    buttons.push_back(button); // Добавляем кнопку в вектор кнопок
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // Устанавливаем голубой цвет фона
    SDL_RenderClear(renderer);                      // Очищаем экран

    for (Button& button : buttons) {
        button.render(renderer); // Отрисовываем каждую кнопку
    }
    SDL_RenderPresent(renderer);                   // Обновляем экран
}

void Menu::handleInput(SDL_Event& event, bool& isRunning) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        // Если произошло нажатие левой кнопки мыши
        int mouseX = event.button.x; // Получаем X координату клика
        int mouseY = event.button.y; // Получаем Y координату клика

        for (Button& button : buttons) {
            if (button.isClicked(mouseX, mouseY)) {
                // Если клик попал на кнопку
                if (button.getText() == "Выход") {
                    isRunning = false; // Если нажали кнопку "Выход", завершаем программу
                    return; // Преждевременный возврат для предотвращения дальнейшей обработки
                }
                button.setClicked(true); // Устанавливаем флаг нажатия кнопки
            }
            else {
                button.setClicked(false); // Снимаем флаг нажатия с остальных кнопок
            }
        }
    }
}