#include <iostream>
#include <stdlib.h>
#include <vector>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

static const char* kFontPath = "./assets/Roboto-Regular.ttf";
static constexpr int kFontSize= 10;

static constexpr int kScreenWidth = 800;
static constexpr int kScreenHeight= 600;

static const std::chrono::nanoseconds kTickLengthNs (static_cast<uint64_t>(1e9/60.0));

namespace game {
    // Bind the SDL structs together
    struct App {
        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<SDL_Texture*> textures;
    };

    App init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("error initializing SDL: %s\n", SDL_GetError());
            exit(2);
        }

        game::App app;
        app.window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenWidth, kScreenHeight, 0);
        if (!app.window) {
            printf("error initializing a (%d, %d) window: %s\n", kScreenWidth, kScreenHeight, SDL_GetError());
            exit(2);
        }
        app.renderer = SDL_CreateRenderer(app.window, 0, SDL_RENDERER_ACCELERATED);
        if (!app.renderer)
        {
            printf("Failed to create renderer: %s\n", SDL_GetError());
            exit(2);
        }
        return app;
    }

    void teardown(App& app) {
        SDL_DestroyWindow(app.window);
        SDL_DestroyRenderer(app.renderer);
        for (SDL_Texture* texture: app.textures) {
            SDL_DestroyTexture(texture);
        }
    }

    void tick(bool& loop) {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                loop = false;
                return;
            case SDL_SCANCODE_SPACE:
                std::cout << "space";
        }
    }

}

int main(int argc, char *argv[])
{
    game::App app = game::init();
    
    bool loop = true;
    std::chrono::nanoseconds prev_tick_time = std::chrono::high_resolution_clock::now().time_since_epoch();
    while (loop) {
        // Lock the tick to a constant frame rate
        const std::chrono::nanoseconds cur_tick_time = std::chrono::high_resolution_clock::now().time_since_epoch();
        if (kTickLengthNs > cur_tick_time - prev_tick_time) {
            continue;
        }
        prev_tick_time = cur_tick_time;
        // Update the game state
        game::tick(loop);
        if (!loop) {
            break;
        }
    }

    game::teardown(app);
    return 0;
}