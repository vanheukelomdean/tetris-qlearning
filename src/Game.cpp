#include "Control.h"
#include "Tetromino.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

static const char* kRandomMode = "random";
static constexpr int kFontSize= 10;

static constexpr int kScreenWidth = 600;
static constexpr int kScreenHeight= 1200;

static const std::chrono::nanoseconds kTickLengthNs (static_cast<uint64_t>(1e9/60.0));

namespace game {
    // Bind the SDL structs together
    struct Video {
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<SDL_Texture*> textures;
    };

    Video init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
            exit(2);
        }

        game::Video video;
        video.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, 0);
        if (!video.window) {
            printf("error initializing a (%d, %d) window: %s\n", kScreenWidth, kScreenHeight, SDL_GetError());
            exit(2);
        }
        video.renderer = SDL_CreateRenderer(video.window, 0, SDL_RENDERER_ACCELERATED);
        if (!video.renderer)
        {
            printf("Failed to create renderer: %s\n", SDL_GetError());
            exit(2);
        }
        return video;
    }

    void teardown(Video& video) {
        SDL_DestroyWindow(video.window);
        SDL_DestroyRenderer(video.renderer);
        for (SDL_Texture* texture: video.textures) {
            SDL_DestroyTexture(texture);
        }
    }
}

int main(int argc, char *argv[])
{
    // Seed a prng if playing in random mode
    bool loop = true;

    game::Video video = game::init();

    std::chrono::nanoseconds prev_tick_time = std::chrono::high_resolution_clock::now().time_since_epoch();
    while (loop) {
        // Lock the tick to a constant frame rate
        const std::chrono::nanoseconds cur_tick_time = std::chrono::high_resolution_clock::now().time_since_epoch();
        if (kTickLengthNs > cur_tick_time - prev_tick_time) {
            continue;
        }
        prev_tick_time = cur_tick_time;
        
        control::Move move = control::getMove(loop);
        // Update the game state
        if (!loop) {
            break;
        }
    }

    game::teardown(video);
    return 0;
}