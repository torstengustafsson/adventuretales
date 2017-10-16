cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME AdventureTales)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(OpenGL REQUIRED)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

 #set the default path for built executables to the "bin" directory
 set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

 #set the default path for built libraries to the "lib" directory
 set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

 #Specify Include Directory
 set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

#Set SDL2 path (TODO: find it instead or hardcoding it)
set(SDL2_DIR "D:/Libraries/SDL2")

include_directories("${SDL2_DIR}/SDL2_image-2.0.1/include")
include_directories("${SDL2_DIR}/SDL2-2.0.5/include")
include_directories("${SDL2_DIR}/SDL2_ttf-2.0.14/include")

set(SDL2_LIBRARY
      ${SDL2_DIR}/SDL2-2.0.5/lib/x64/SDL2.lib
      ${SDL2_DIR}/SDL2-2.0.5/lib/x64/SDL2main.lib
      ${SDL2_DIR}/SDL2_ttf-2.0.14/lib/x64/SDL2_ttf.lib
      ${SDL2_DIR}/SDL2_image-2.0.1/lib/x64/SDL2_image.lib )

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
       include/world/src/Player.cpp )

file(GLOB_RECURSE HEADER_FILES "*.h")


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

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${SDL2_LIBRARY})