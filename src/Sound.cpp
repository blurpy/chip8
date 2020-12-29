#include <iostream>

#include "Sound.h"

Sound::Sound() : frequency(500),
                 sampleRate(48000),
                 position(0),
                 playing(false),
                 audioDevice(0) {
    init();

    std::cout << "Sound in" << std::endl;
}

Sound::~Sound() {
    SDL_CloseAudioDevice(audioDevice);
    SDL_CloseAudio();

    std::cout << "Sound out" << std::endl;
}

bool Sound::init() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL Init audio failed: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_AudioSpec wantSpec, haveSpec;

    SDL_zero(wantSpec);
    wantSpec.freq = sampleRate;
    wantSpec.format = AUDIO_U8;
    wantSpec.channels = 1;
    wantSpec.samples = 2048;
    wantSpec.callback = SDLAudioCallback;
    wantSpec.userdata = this;

    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &wantSpec, &haveSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (audioDevice == 0) {
        std::cerr << "SDL open audio device failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // What we ask for and what we get might not be the same
    sampleRate = haveSpec.freq;

    return true;
}

void Sound::play() {
    if (playing) {
        return;
    }

    playing = true;
    SDL_PauseAudioDevice(audioDevice, 0);
}

void Sound::pause() {
    if (!playing) {
        return;
    }

    SDL_PauseAudioDevice(audioDevice, 1);
    position = 0; // Start at a known location the next time sound plays
    playing = false;
}

void Sound::SDLAudioCallback(void *userData, Uint8 *buffer, int length) {
    auto *instance = reinterpret_cast<Sound*>(userData); // userData is an instance of this class

    // Generate a sample of a sine wave at the specified frequency based on the current position.
    // There is often a "pop" when sound is paused, so this can probably be improved.
    for (int i = 0; i < length; ++i) {
        double value = instance->position * instance->frequency / instance->sampleRate * M_PI * 2.0;
        double sine = std::sin(value);

        buffer[i] = (sine + 1.0) * 127.5;
        ++instance->position;
    }
}
