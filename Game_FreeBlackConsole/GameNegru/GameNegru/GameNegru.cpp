#include "Game.h"
#include "Menu.h"
#include "Button.h"
#include "Player.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game game; // �������� ���������� ������ Game

    if (!game.init()) {
        std::cerr << "������������� ���� �� �������!" << std::endl;
        return 1;  // ���� ������������� �� �������, ��������� ���������
    }
    SDL_Renderer* renderer = game.getRenderer(); // ��������� ��������� �� ��������

    Menu menu; // �������� ���������� ������ Menu
    Button startButton(700, 300, 200, 100, "�����", ""); // �������� ������ "�����"
    Button exitButton(700, 500, 200, 100, "�����", "");  // �������� ������ "�����"
    menu.addButton(startButton); // ���������� ������ "�����" � ����
    menu.addButton(exitButton);  // ���������� ������ "�����" � ����

    bool isRunning = true; // ����, ������������, �������� �� ����
    SDL_Event event;      // ���������� ��� �������� �������

    while (isRunning) {
        // ������� ���� ����
        while (SDL_PollEvent(&event)) {
            // ���� ��������� �������
            if (event.type == SDL_QUIT) {
                isRunning = false; // ���� ������ �� ������� ����, ��������� ����
            }
            menu.handleInput(event, isRunning); // ��������� ������� � ����
        }
        menu.render(renderer); // ��������� ����

        if (startButton.getClicked())
        {
            // ���� ������ ������ "�����", �������� ����
            Player player(100, 100, renderer); // �������� ������

            SDL_Event event_game;
            bool isGameRunning = true; // ����, ������������, �������� �� ����

            while (isGameRunning) {
                // ���� ����
                while (SDL_PollEvent(&event_game)) {
                    if (event_game.type == SDL_QUIT) {
                        isGameRunning = false;
                        isRunning = false;  // ���� ������� ����, ��������� ����
                    }
                    if (event_game.type == SDL_KEYDOWN) {
                        if (event_game.key.keysym.sym == SDLK_ESCAPE)
                        {
                            isGameRunning = false; // ���� ������ ESC, ��������� ����
                        }
                    }
                }

                const Uint8* keyboardState = SDL_GetKeyboardState(nullptr); // �������� ��������� ����������
                player.handleInput(keyboardState); // ������������ ���� ������

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // ������������� ������ ����
                SDL_RenderClear(renderer);                      // ������� ������

                player.draw(renderer);  // ��������� ������
                SDL_RenderPresent(renderer);                   // ���������� ������

                if (player.hasReachedExit()) {
                    isGameRunning = false; // ���� ����� ������ ������, ��������� ����
                }
            }
            startButton.setClicked(false); // ���������� ���� ������� ������ "�����"
        }
    }
    return 0; // ���������� ���������
}