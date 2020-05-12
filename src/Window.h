#ifndef CHIP8_WINDOW_H
#define CHIP8_WINDOW_H

#include <memory>
#include <vector>

#include "SDL2/SDL.h"

#include "Keyboard.h"

class Window {

public:
    Window(std::string windowTitle, int scale, std::shared_ptr<Keyboard> keyboard);
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

    std::shared_ptr<Keyboard> keyboard;
    std::string windowTitle;
    int width;
    int height;
    int scale;

    bool closed;
    bool dirty;

    int pixelSize;
    std::vector<uint8_t> pixels;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    bool init();
};

#endif //CHIP8_WINDOW_H
