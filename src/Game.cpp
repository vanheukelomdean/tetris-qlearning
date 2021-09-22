#include "Control.h"
#include "Tetromino.h"
#include "Utils.h"

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

static constexpr int kXTiles = 10;
static constexpr int kYTiles = 20;

static constexpr int kTileOuterSize = 60;
static constexpr int kTileMargin = 2;
static const int kTileInnerSize = kTileOuterSize - 2 * kTileMargin;

static const std::chrono::nanoseconds kTickLengthNs (static_cast<uint64_t>(1e9/60.0));

namespace game {
    // Bind the SDL structs together
    struct Video {
        SDL_Window* window;
        SDL_Renderer* renderer;
    };

    Video init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
            exit(2);
        }
        bool result;

        game::Video video;
        video.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, 0);
        CHECK_SDL_WARNING(video.window ,result);
        
        video.renderer = SDL_CreateRenderer(video.window, 2, SDL_RENDERER_ACCELERATED);

        SDL_Surface* background_surface = SDL_GetWindowSurface(video.window);

        Uint32 green = SDL_MapRGB(background_surface->format, 255, 255, 255);
        SDL_FillRect(background_surface, NULL, green);
        SDL_UpdateWindowSurface(video.window);

        // SDL_Surface* blank_tile_surface = SDL_CreateRGBSurface(0, kTileInnerSize, kTileInnerSize, 1, 0, 0, 0, 0);
        // if (!blank_tile_surface) {
        //     std::cout << SDL_GetError();
        //     exit(2);
        // }
        // // std::cout << "here" << std::endl; exit(2);

        // Uint32 other = SDL_MapRGB(blank_tile_surface->format, 50, 100, 100);

        // const int num_tiles = kXTiles * kYTiles;
        // SDL_Rect* rects = new SDL_Rect [num_tiles];

        // for (size_t row = 0; row < kYTiles; ++row) {
        //     for (size_t col = 0; col < kXTiles; ++col) {
        //         SDL_Rect& rect = rects[col + row * kXTiles];
        //         rect.x = col * kTileOuterSize + kTileMargin;
        //         rect.w = kTileInnerSize;
        //         rect.y = row * kTileOuterSize + kTileMargin;
        //         rect.h = kTileInnerSize;
        //         std::cout << rect.x << ", " << rect.y << " - "  << rect.w << ", " << rect.h << std::endl;
        //     }
        // }
        // SDL_FillRects(blank_tile_surface, rects, num_tiles, 0);
        SDL_RenderClear(video.renderer); 
        SDL_RenderPresent(video.renderer);
        
        delete background_surface;
        // delete blank_tile_surface;
        // delete [] rects;

        return video;
    }

    void teardown(Video& video) {
        SDL_DestroyWindow(video.window);
        SDL_DestroyRenderer(video.renderer);
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