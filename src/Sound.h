#ifndef CHIP8_SOUND_H
#define CHIP8_SOUND_H

#include "SDL2/SDL.h"

class Sound {

public:
    Sound();
    ~Sound();

    void play();
    void pause();

private:
    double frequency;
    double sampleRate;
    uint32_t position;
    bool playing;
    SDL_AudioDeviceID audioDevice;

    bool init();

    static void SDLAudioCallback(void *userData, Uint8 *buffer, int length);
};

#endif //CHIP8_SOUND_H
