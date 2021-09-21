#include "Control.h"

#include <iostream>

#include <SDL2/SDL_events.h>

namespace control {
    Move getMove(bool& loop) {
        SDL_Event event;
        SDL_PollEvent(&event);
        Move last_keydown_event = Move::None;
        switch (event.type) {
            case SDL_QUIT:
                loop = false;
                return None;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                        last_keydown_event = Move::Left;
                    case SDLK_d:
                        last_keydown_event = Move::Right;
                    case SDLK_s:
                        last_keydown_event = Move::Fall;
                    default:
                        break;
                }
            default:
                break;
        }
        return last_keydown_event;
    }
}