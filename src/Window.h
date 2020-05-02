#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include "SDL2/SDL.h"

class Window {

public:
    Window(const std::string& windowTitle, int scale);
    ~Window();

    void pollEvents();

    bool isClosed() const;
    void show();

    void clearScreen();

private:
    static const int ORIGINAL_WIDTH = 64;
    static const int ORIGINAL_HEIGHT = 32;

    std::string windowTitle;
    int width;
    int height;
    int scale;

    bool closed;

    SDL_Window *window;
    SDL_Renderer *renderer;

    bool init();
};

#endif //CHIP8_WINDOW_H
