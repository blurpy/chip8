#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H

#include <vector>

#include "SDL2/SDL.h"

class Keyboard {

public:
    Keyboard();
    ~Keyboard();

    void handleKeyUp(SDL_KeyboardEvent keyboardEvent);
    void handleKeyDown(SDL_KeyboardEvent keyboardEvent);
    bool keyIsPressed(uint8_t key);

private:
    std::vector<bool> keyboard = std::vector<bool>(16, false);

};

#endif //CHIP8_KEYBOARD_H
