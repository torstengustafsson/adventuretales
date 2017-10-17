em++ -O2 ^
-std=c++11 ^
-s USE_SDL=2 ^
-s USE_SDL_IMAGE=2 ^
-s SDL2_IMAGE_FORMATS="[""png""]" ^
-s USE_SDL_TTF=2 ^
include/main_js.cpp ^
-Iinclude ^
-ID:\Projects\adventuretales\include ^
-ID:\Libraries\SDL2\SDL2_image-2.0.1\include ^
-ID:\Libraries\SDL2\SDL2-2.0.5\include ^
-ID:\Libraries\SDL2\SDL2_ttf-2.0.14\include ^
--preload-file data ^
-o adventuretales.html