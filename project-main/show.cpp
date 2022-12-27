#include "sokoban.h"

void show_manual(SDL_Surface *screen, SDL_Surface *manual, SDL_Rect &p_manual)
{
    // show manual
    SDL_Event event;
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(manual, NULL, screen, &p_manual);
    SDL_Flip(screen);
    int temp = 1;
    while (temp)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            temp = 0;
            SDL_FreeSurface(manual);
            return;
        }
    }
}
