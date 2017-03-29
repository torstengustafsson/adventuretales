cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME AdventureTales)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(OpenGL REQUIRED)

include_directories("include")
include_directories(${OPENGL_INCLUDE_DIR})

# TODO: SDL path should not be hardcoded
include_directories("D:/Libraries/SDL2/SDL2_image-2.0.1/include")
include_directories("D:/Libraries/SDL2/SDL2-2.0.5/include")
include_directories("D:/Libraries/SDL2/SDL2_ttf-2.0.14/include")

set( SDL2_LIBRARY 
		D:/Libraries/SDL2/SDL2-2.0.5/lib/x86/SDL2.lib
		D:/Libraries/SDL2/SDL2-2.0.5/lib/x86/SDL2main.lib
		D:/Libraries/SDL2/SDL2_ttf-2.0.14/lib/x86/SDL2_ttf.lib
		D:/Libraries/SDL2/SDL2_image-2.0.1/lib/x86/SDL2_image.lib )

set( SOURCE_FILES
       include/main.cpp
       include/core/AdventureTales.cpp
       include/core/DialogueGenerator.cpp
       include/core/GameController.cpp
       include/core/GameEngine.cpp
       include/core/GameRenderer.cpp
       include/core/InputHandler.cpp
       include/core/MapHandler.cpp
       include/core/PlayerData.cpp
       include/core/RandomGenerator.cpp
       include/core/Resources.cpp
       include/characters/Character.cpp 
       include/characters/Archer.cpp 
       include/characters/Viking.cpp 
       include/characters/Traits.cpp 
       include/characters/Inventory.cpp
       include/items/Item.cpp
       include/items/Armor.cpp
       include/items/Potion.cpp
       include/items/Scroll.cpp
       include/items/Weapon.cpp
       include/menu/InteractionMenu.cpp
       include/menu/MainMenu.cpp
       include/menu/Menu.cpp
       include/menu/MenuBattle.cpp
       include/menu/MenuWorld.cpp
       include/textures/Text.cpp
       include/textures/Texture.cpp
       include/world/Camera.cpp
       include/world/Door.cpp
       include/world/Enemy.cpp
       include/world/MovingObject.cpp
       include/world/NPC.cpp
       include/world/Object.cpp
       include/world/Player.cpp )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY})