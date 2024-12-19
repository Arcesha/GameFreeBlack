#include "Menu.h"
#include <iostream>

Menu::Menu() {
    // ����������� ������ Menu
}

Menu::~Menu() {
    // ���������� ������ Menu
}

void Menu::addButton(Button button) {
    buttons.push_back(button); // ��������� ������ � ������ ������
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 255); // ������������� ������� ���� ����
    SDL_RenderClear(renderer);                      // ������� �����

    for (Button& button : buttons) {
        button.render(renderer); // ������������ ������ ������
    }
    SDL_RenderPresent(renderer);                   // ��������� �����
}

void Menu::handleInput(SDL_Event& event, bool& isRunning) {
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        // ���� ��������� ������� ����� ������ ����
        int mouseX = event.button.x; // �������� X ���������� �����
        int mouseY = event.button.y; // �������� Y ���������� �����

        for (Button& button : buttons) {
            if (button.isClicked(mouseX, mouseY)) {
                // ���� ���� ����� �� ������
                if (button.getText() == "�����") {
                    isRunning = false; // ���� ������ ������ "�����", ��������� ���������
                    return; // ��������������� ������� ��� �������������� ���������� ���������
                }
                button.setClicked(true); // ������������� ���� ������� ������
            }
            else {
                button.setClicked(false); // ������� ���� ������� � ��������� ������
            }
        }
    }
}