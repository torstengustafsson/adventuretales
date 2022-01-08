cmake_minimum_required(VERSION 3.13)

project(Adventuretales)

add_subdirectory("ext/SDL2")
add_subdirectory("ext/SDL2_image")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# NOTE: (As of 2022/01/07) SDL_ttf does not work very well with CMake, so we use prebuilt .libs and includes directly
# add_subdirectory("ext/SDL2_ttf")
set(SDL_TTF_INCLUDE_DIR "ext/SDL2_ttf/SDL2_ttf-2.0.15-VC/include")
set(SDL_TTF_LIB_DIR_x64 "ext/SDL2_ttf/SDL2_ttf-2.0.15-VC/lib/x64")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")

find_package(OpenGL REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set( PROJECT_SOURCE_FILES
       include/main.cpp
       include/core/src/AdventureTales.cpp
       include/core/src/DialogueGenerator.cpp
       include/core/src/GameController.cpp
       include/core/src/GameEngine.cpp
       include/core/src/GameRenderer.cpp
       include/core/src/InputHandler.cpp
       include/core/src/MapHandler.cpp
       include/core/src/PlayerData.cpp
       include/core/src/RandomGenerator.cpp
       include/core/src/Resources.cpp
       include/characters/src/Character.cpp
       include/characters/src/Archer.cpp
       include/characters/src/Viking.cpp
       include/characters/src/Traits.cpp
       include/characters/src/Inventory.cpp
       include/enemies/src/Enemy.cpp
       include/items/src/Item.cpp
       include/items/src/Armor.cpp
       include/items/src/Potion.cpp
       include/items/src/Scroll.cpp
       include/items/src/Weapon.cpp
       include/menu/src/InteractionMenu.cpp
       include/menu/src/MainMenu.cpp
       include/menu/src/Menu.cpp
       include/menu/src/MenuBattle.cpp
       include/menu/src/MenuWorld.cpp
       include/textures/src/Text.cpp
       include/textures/src/Texture.cpp
       include/world/src/Camera.cpp
       include/world/src/Door.cpp
       include/world/src/MovingObject.cpp
       include/world/src/NPC.cpp
       include/world/src/Object.cpp
       include/world/src/Player.cpp
      )

file(GLOB_RECURSE HEADER_FILES "*.h")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    "include"
    "ext/SDL2/include"
    "ext/SDL2_image"
    ${SDL_TTF_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
  )

# The below macro was shamelessly stolen from:
# https://cmake.org/pipermail/cmake/2013-November/056336.html

# Organize the files in visual studio folders, according to
# the organization in the file systems
macro(GroupSources curdir)
  file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)
    foreach(child ${children})
      if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        GroupSources(${curdir}/${child})
      else()
        string(REPLACE "/" "\\" groupname ${curdir})
        source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
      endif()
  endforeach()
endmacro()

# Execute the macro
GroupSources("include")

target_link_directories(${PROJECT_NAME} PRIVATE ${SDL_TTF_LIB_DIR_x64})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} SDL2 SDL2_image SDL2_ttf.lib)
#target_link_options(${PROJECT_NAME} PRIVATE "/entry:mainCRTStartup")
