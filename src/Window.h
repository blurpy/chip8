#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include "SDL2/SDL.h"

class Window {

private:
    std::string windowTitle;
    int width;
    int height;
    SDL_Window *window;
    bool closed;

    bool init();

public:
    Window(const std::string& windowTitle, int width, int height);
    ~Window();

    void pollEvents();
    bool isClosed();
};

#endif //CHIP8_WINDOW_H
