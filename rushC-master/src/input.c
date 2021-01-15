#include <SDL2/SDL.h>
#include "input.h"

struct input get_inputs()
{
    SDL_PumpEvents();
    struct input input;
    for (int i = 0; i < NUMBER_KEYS; i++)
    {
        input.inputs[i] = 0;
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
        input.inputs[QUIT] = 1;
    if (state[SDL_SCANCODE_SPACE])
        input.inputs[SPACE] = 1;
    if (state[SDL_SCANCODE_LEFT])
        input.inputs[LEFT] = 1;
    if (state[SDL_SCANCODE_RIGHT])
        input.inputs[RIGHT] = 1;
    if (state[SDL_SCANCODE_S])
        input.inputs[SHOOT] = 1;
    if (state[SDL_SCANCODE_N])
        input.inputs[NEXT] = 1;
    return input;
}
