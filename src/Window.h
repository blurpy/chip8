#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <vector>

#include "SDL2/SDL.h"

class Window {

public:
    Window(const std::string& windowTitle, int scale);
    ~Window();

    void pollEvents();

    bool isClosed() const;
    void show();

    bool drawSpritePixel(unsigned int x, unsigned int y);
    void redraw();
    void clearScreen();

private:
    static const int ORIGINAL_WIDTH = 64;
    static const int ORIGINAL_HEIGHT = 32;
    static const int WHITE = 255;

    std::string windowTitle;
    int width;
    int height;
    int scale;

    bool closed;

    int pixelSize;
    std::vector<uint8_t> pixels;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    bool init();
};

#endif //CHIP8_WINDOW_H
