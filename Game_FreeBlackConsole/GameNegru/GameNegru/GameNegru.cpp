#include "Game.h"
#include "Menu.h"
#include "Button.h"
#include "Player.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game; // Создание экземпляра класса Game

    if (!game.init()) {
        std::cerr << "Инициализация игры не удалась!" << std::endl;
        return 1;  // Если инициализация не удалась, завершаем программу
    }
    SDL_Renderer* renderer = game.getRenderer(); // Получение указателя на рендерер

    Menu menu; // Создание экземпляра класса Menu
    Button startButton(700, 300, 200, 100, "Старт", ""); // Создание кнопки "Старт"
    Button exitButton(700, 500, 200, 100, "Выход", "");  // Создание кнопки "Выход"
    menu.addButton(startButton); // Добавление кнопки "Старт" в меню
    menu.addButton(exitButton);  // Добавление кнопки "Выход" в меню

    bool isRunning = true; // Флаг, определяющий, работает ли игра
    SDL_Event event;      // Переменная для хранения событий

    while (isRunning) {
        // Главный цикл игры
        while (SDL_PollEvent(&event)) {
            // Цикл обработки событий
            if (event.type == SDL_QUIT) {
                isRunning = false; // Если нажали на крестик окна, завершаем игру
            }
            menu.handleInput(event, isRunning); // Обработка событий в меню
        }
        menu.render(renderer); // Отрисовка меню

        if (startButton.getClicked())
        {
            // Если нажали кнопку "Старт", начинаем игру
            Player player(100, 100, renderer); // Создание игрока

            SDL_Event event_game;
            bool isGameRunning = true; // Флаг, определяющий, запущена ли игра

            while (isGameRunning) {
                // Цикл игры
                while (SDL_PollEvent(&event_game)) {
                    if (event_game.type == SDL_QUIT) {
                        isGameRunning = false;
                        isRunning = false;  // Если закрыли окно, завершаем игру
                    }
                    if (event_game.type == SDL_KEYDOWN) {
                        if (event_game.key.keysym.sym == SDLK_ESCAPE)
                        {
                            isGameRunning = false; // Если нажали ESC, завершаем игру
                        }
                    }
                }

                const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // Получаем состояние клавиатуры
                player.handleInput(keyboardState); // Обрабатываем ввод игрока

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Устанавливаем черный цвет
                SDL_RenderClear(renderer);                      // Очистка экрана

                player.draw(renderer);  // Отрисовка игрока
                SDL_RenderPresent(renderer);                   // Обновление экрана

                if (player.hasReachedExit()) {
                    isGameRunning = false; // Если игрок достиг выхода, завершаем игру
                }
            }
            startButton.setClicked(false); // Сбрасываем флаг нажатия кнопки "Старт"
        }
    }
    return 0; // Завершение программы
}