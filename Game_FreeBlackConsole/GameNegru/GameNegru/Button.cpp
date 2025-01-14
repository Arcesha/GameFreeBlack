#include "Button.h"
#include <iostream>

Button::Button(int x, int y, int width, int height, const std::string& text, const std::string& imagePath)
    : text(text), clicked(false) // ����������� ������ Button, ������������� �����
{
    rect.x = x;    // ���������� X ������
    rect.y = y;    // ���������� Y ������
    rect.w = width; // ������ ������
    rect.h = height; // ������ ������

    texture = nullptr; // ���������� �������� �� ������
    if (!imagePath.empty()) {
        // ���� ���� � ����������� �� ������
        SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str()); // ��������� �����������
        if (!surface) {
            std::cerr << "�� ������� ��������� �����������: " << imagePath << " SDL_Error: " << SDL_GetError() << std::endl;
            return; // ���� �������� �� �������, ������� �� ������������
        }
        texture = SDL_CreateTextureFromSurface(SDL_GetRenderer(SDL_GetWindowFromID(1)), surface);
        // ������� �������� �� ������������ �����������
        SDL_FreeSurface(surface); // ���02�������� ����������� ����� �������� ��������
        if (!texture) {
            std::cerr << "�� ������� ������� �������� �� ����������� SDL_Error: " << SDL_GetError() << std::endl;
        }
    }
}

Button::~Button() {
    if (texture) {
        SDL_DestroyTexture(texture); // ������������ �������� ��������
    }
}

void Button::render(SDL_Renderer* renderer) {
    if (texture) {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        // ���� �������� ����, ������������ ��
    }
    else {
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // ������������� ����� ���� ������
        SDL_RenderFillRect(renderer, &rect);                 // ������ �������������
    }
}

bool Button::isClicked(int mouseX, int mouseY) {
    if (mouseX > rect.x && mouseX < rect.x + rect.w &&
        mouseY > rect.y && mouseY < rect.y + rect.h) {
        // ���������, �������� �� ���� � ������� ������
        return true; // ���������� true, ���� ���� �����
    }
    return false; // ���������� false, ���� ���� �� �����
}

const std::string& Button::getText() const {
    return text; // ���������� ����� ������
}

void Button::setClicked(bool isClicked) {
    this->clicked = isClicked; // ������������� ���� ������� ������
}

bool Button::getClicked() const {
    return clicked; // ���������� ���� ������� ������
}