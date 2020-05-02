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
    void clearScreen();

private:
    std::string windowTitle;
    int width;
    int height;
    bool closed;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool init();
};

#endif //CHIP8_WINDOW_H
