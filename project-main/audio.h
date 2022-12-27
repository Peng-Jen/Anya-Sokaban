#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL.h>
#include <SDL2/SDL_audio.h>
#include <string>
// using namespace std;

class Audio
{
private:
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;

public:
    ~Audio();
    void load(std::string filename);
    void play();
};

#endif // AUDIO_H
