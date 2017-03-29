Requires SDL2 to run. I have been lazy and linked my local SDL path in the CMakeLists file, so to compile you need to either add your own local paths or fix a more general solution :)

This project was originally developed in Linux using CodeLite and a simple makefile. I later added the CMake file to compile it on Windows. I have not thested this CMake code more than for Visual Studio 2017, which it works for.

The file path to textures and other resources are currently hardcoded for the data folder to be one layer up (like this: path = ../data/sprites/some_image.png), so if you use custom paths you will have to change these manually.

If you use Windows, move the files from the 'dll' folder to your binary folder to run the project.

Uses:
SDL2 		- https://www.libsdl.org/download-2.0.php
SDL2_image 	- https://www.libsdl.org/projects/SDL_image/
SDL2_ttf	- https://www.libsdl.org/projects/SDL_ttf/