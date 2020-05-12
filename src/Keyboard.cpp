#include <iostream>

#include "Keyboard.h"

/**
 * The hex keypad looks like this. The numbers are opposite direction of a numpad.
 * The keys are mapped directly to the keys they represent for now, so 1 is 1 and A is A.
 *
 * +-+-+-+-+
 * |1|2|3|C|
 * +-+-+-+-+
 * |4|5|6|D|
 * +-+-+-+-+
 * |7|8|9|E|
 * +-+-+-+-+
 * |A|0|B|F|
 * +-+-+-+-+
 */
Keyboard::Keyboard() {
    std::cout << "Keyboard in" << std::endl;
}

Keyboard::~Keyboard() {
    std::cout << "Keyboard out" << std::endl;
}

void Keyboard::handleKeyUp(SDL_KeyboardEvent keyboardEvent) {
    SDL_Keycode keycode = keyboardEvent.keysym.sym;

    if (keycode == SDLK_0 || keycode == SDLK_KP_0) {
        keyboard[0] = false;
    } else if (keycode == SDLK_1 || keycode == SDLK_KP_1) {
        keyboard[1] = false;
    } else if (keycode == SDLK_2 || keycode == SDLK_KP_2) {
        keyboard[2] = false;
    } else if (keycode == SDLK_3 || keycode == SDLK_KP_3) {
        keyboard[3] = false;
    } else if (keycode == SDLK_4 || keycode == SDLK_KP_4) {
        keyboard[4] = false;
    } else if (keycode == SDLK_5 || keycode == SDLK_KP_5) {
        keyboard[5] = false;
    } else if (keycode == SDLK_6 || keycode == SDLK_KP_6) {
        keyboard[6] = false;
    } else if (keycode == SDLK_7 || keycode == SDLK_KP_7) {
        keyboard[7] = false;
    } else if (keycode == SDLK_8 || keycode == SDLK_KP_8) {
        keyboard[8] = false;
    } else if (keycode == SDLK_9 || keycode == SDLK_KP_9) {
        keyboard[9] = false;
    } else if (keycode == SDLK_a) {
        keyboard[10] = false;
    } else if (keycode == SDLK_b) {
        keyboard[11] = false;
    } else if (keycode == SDLK_c) {
        keyboard[12] = false;
    } else if (keycode == SDLK_d) {
        keyboard[13] = false;
    } else if (keycode == SDLK_e) {
        keyboard[14] = false;
    } else if (keycode == SDLK_f) {
        keyboard[15] = false;
    }
}

void Keyboard::handleKeyDown(SDL_KeyboardEvent keyboardEvent) {
    SDL_Keycode keycode = keyboardEvent.keysym.sym;

    if (keycode == SDLK_0 || keycode == SDLK_KP_0) {
        keyboard[0] = true;
    } else if (keycode == SDLK_1 || keycode == SDLK_KP_1) {
        keyboard[1] = true;
    } else if (keycode == SDLK_2 || keycode == SDLK_KP_2) {
        keyboard[2] = true;
    } else if (keycode == SDLK_3 || keycode == SDLK_KP_3) {
        keyboard[3] = true;
    } else if (keycode == SDLK_4 || keycode == SDLK_KP_4) {
        keyboard[4] = true;
    } else if (keycode == SDLK_5 || keycode == SDLK_KP_5) {
        keyboard[5] = true;
    } else if (keycode == SDLK_6 || keycode == SDLK_KP_6) {
        keyboard[6] = true;
    } else if (keycode == SDLK_7 || keycode == SDLK_KP_7) {
        keyboard[7] = true;
    } else if (keycode == SDLK_8 || keycode == SDLK_KP_8) {
        keyboard[8] = true;
    } else if (keycode == SDLK_9 || keycode == SDLK_KP_9) {
        keyboard[9] = true;
    } else if (keycode == SDLK_a) {
        keyboard[10] = true;
    } else if (keycode == SDLK_b) {
        keyboard[11] = true;
    } else if (keycode == SDLK_c) {
        keyboard[12] = true;
    } else if (keycode == SDLK_d) {
        keyboard[13] = true;
    } else if (keycode == SDLK_e) {
        keyboard[14] = true;
    } else if (keycode == SDLK_f) {
        keyboard[15] = true;
    }
}

bool Keyboard::keyIsPressed(uint8_t key) {
    if (key < keyboard.size()) {
        return keyboard[key] == true;
    }

    return false;
}
