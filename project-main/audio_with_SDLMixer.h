#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <iostream>
#include <string>

class Audio
{
    private:
        //Background music
        Mix_Music *background;
        //Sound effects
        Mix_Chunk *waku;
        Mix_Chunk *eleganto;
        Mix_Chunk *okidoki;
        Mix_Chunk *peanuts;
        Mix_Chunk *anya_fail;
    public:
        // Constructor: Initializes SDL Mixer and loads sound effects
        Audio();
        // Destructor: Free all sound effects
        // ~Audio();
        // Play sound effects
        void playBackground();
        void playWaku();
        void playEleganto();
        void playOkiDoki();
        void playPeanuts();
        void playAnyaFail();

};
