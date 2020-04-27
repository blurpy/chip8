#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include "SDL2/SDL.h"

class Window {

public:
    Window(const std::string& windowTitle, int width, int height);
    ~Window();

    void pollEvents();
    bool isClosed() const;

    void show();

private:
    std::string windowTitle;
    int width;
    int height;
    SDL_Window *window;
    bool closed;

    bool init();
};

#endif //CHIP8_WINDOW_H
