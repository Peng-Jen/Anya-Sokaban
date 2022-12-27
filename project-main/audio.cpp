#include "audio.h"
// Load audio
void Audio::load(std::string filename)
{
    const char *filename_ptr = filename.c_str();
    SDL_RWops *io = SDL_RWFromFile(filename_ptr, "rb");
    SDL_LoadWAV_RW(io, 1, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0); // Default
}
// Play audio
void Audio::play()
{
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0); // 0: false
}
// Destructor
Audio::~Audio()
{
    SDL_CloseAudio();
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}
/*
主程式的Init改為：
    SDL_Init(SDL_INIT_EVERYTHING);
主程式中需建立Audio物件：
    Audio sound;
在需要播放音效的地方加上：
    sound.load("filename.wav");
    sound.play();
*/
