#include "../src/Utils.h"

#define BOOST_TEST_MODULE Utils

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_CASE( nullptr_check )
{
    SDL_Window* dummy_window = nullptr;

    BOOST_CHECK( !dummy_window );
    bool result; 
    CHECK_SDL_WARNING(dummy_window, result); 
    BOOST_CHECK(!result);
}

BOOST_AUTO_TEST_CASE( window_check )
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        exit(2);
    }
    bool result;
    SDL_Window* window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, 0);
    CHECK_SDL_WARNING(window, result); 
    BOOST_CHECK(result);
}