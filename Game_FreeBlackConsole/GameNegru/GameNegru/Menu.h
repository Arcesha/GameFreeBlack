#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <vector>
#include "Button.h"

class Menu {
public:
    Menu();
    ~Menu();

    void addButton(Button button);
    void render(SDL_Renderer* renderer);
    void handleInput(SDL_Event& event, bool& isRunning);

private:
    std::vector<Button> buttons;
};

#endif