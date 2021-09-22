#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#define CHECK_SDL_WARNING(s, result) utils::checkSDLWarning(s, result);

namespace utils {
    // Checks validity of SDL Objects. If the object was not correctly
    // initialized, pipe SDL error to output and fail.
    template<typename T>
    inline T* checkSDLWarning(T* s, bool& result = false, const std::string& f = __FUNCTION__, 
                                int loc = __LINE__)
    {
        if (!s) {
            std::cout << "SDL Error from function " << f << " at call site on line " << loc << ": " << SDL_GetError() << std::endl;
            return s;
        }
        result = true;
        return s;
    }
}