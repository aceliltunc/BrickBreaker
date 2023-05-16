#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>
#include "game_header.h"

int main(int argc, char **argv)
{
    srand((unsigned int)time(NULL));
    Initialize();

    bool running = true;
    SDL_Event event;
    Uint32 lastTick = SDL_GetTicks();
    while(running)
    {
        // Process events
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
        }

    Uint32 curTick = SDL_GetTicks();
    Uint32 diff = curTick - lastTick;
    float elapsed = diff / 1000.0f;
    Update(elapsed);
    lastTick = curTick;


    }

    Shutdown();

    return 0;
}
