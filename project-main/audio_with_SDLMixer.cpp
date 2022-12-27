# include "audio_with_SDLMixer.h"
// Constructor
Audio::Audio()
{   
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL Mixer initialize fail!");
        printf("SDL Mixer Error: %s", Mix_GetError());
    }


    Mix_Music *background = nullptr;
    background = Mix_LoadMUS("src/audio/audio_background.wav");
    Mix_Chunk *waku = nullptr;
    waku = Mix_LoadWAV("src/audio/audio_waku.wav");
    Mix_Chunk *eleganto = nullptr;
    eleganto = Mix_LoadWAV("src/audio/audio_eleganto.wav");
    Mix_Chunk *okidoki = nullptr;
    okidoki = Mix_LoadWAV("src/audio/audio_okidoki.wav");
    Mix_Chunk *peanuts = nullptr;
    peanuts = Mix_LoadWAV("src/audio/audio_peanuts.wav");
    Mix_Chunk *anya_fail = nullptr;
    anya_fail = Mix_LoadWAV("src/audio/audio_anya_fail.wav");
}
// Destructor
// Audio::~Audio()
// {
//     Mix_FreeMusic(background);
//     delete background;
//     Mix_FreeChunk(waku);
//     delete waku;
//     Mix_FreeChunk(eleganto);
//     delete eleganto;
//     Mix_FreeChunk(okidoki);
//     delete okidoki;
//     Mix_FreeChunk(peanuts);
//     delete peanuts;
//     Mix_FreeChunk(anya_fail);
//     delete anya_fail;
    
//     Mix_Quit();
// }
// Play sound effects
void Audio::playBackground()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(background, -1); // play and loop for infinite times
    }
}
void Audio::playWaku()
{
    Mix_PlayChannel(-1, waku, 1); // play waku on first unreserved channel for 1 time
}
void Audio::playEleganto()
{
    Mix_PlayChannel(-1, eleganto, 1);
}
void Audio::playOkiDoki()
{
    Mix_PlayChannel(-1, okidoki, 1);
}
void Audio::playPeanuts()
{
    Mix_PlayChannel(-1, peanuts, 1);
}
void Audio::playAnyaFail()
{
    Mix_PlayChannel(-1, anya_fail, 1);
}
