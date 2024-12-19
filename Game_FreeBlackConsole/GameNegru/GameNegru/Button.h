#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include <string>

class Button {
public:
    Button(int x, int y, int width, int height, const std::string& text, const std::string& imagePath);
    ~Button();

    void render(SDL_Renderer* renderer);
    bool isClicked(int mouseX, int mouseY);
    const std::string& getText() const;
    void setClicked(bool isClicked);
    bool getClicked() const;

private:
    SDL_Rect rect;
    std::string text;
    SDL_Texture* texture;
    bool clicked;
};

#endif