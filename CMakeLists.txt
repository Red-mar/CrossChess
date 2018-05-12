

cmake_minimum_required(VERSION 3.7)
# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

set (CMAKE_CXX_STANDARD 11)

project(SDLStructured)
include_directories(src)

if(EMSCRIPTEN)
else()
find_package(ZLIB REQUIRED)
if(NOT ZLIB_FOUND)
	message(FATAL_ERROR "zlib library not found")
endif(NOT ZLIB_FOUND)
include_directories(${ZLIB_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
	message(FATAL_ERROR "SDL2 library not found")
endif(NOT SDL2_FOUND)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
if(NOT SDL2_IMAGE_FOUND)
	message(FATAL_ERROR "SDL2_image library not found")
endif(NOT SDL2_IMAGE_FOUND)
include_directories(${SDL_IMAGE_INCLUDE_DIRS})

find_package(SDL2_mixer REQUIRED)
if(NOT SDL_MIXER_FOUND)
	message(FATAL_ERROR "SDL2_mixer library not found")
endif(NOT SDL_MIXER_FOUND)
include_directories(${SDL_MIXER_INCLUDE_DIRS})
find_package(SDL2_ttf REQUIRED)

if(NOT SDL2_TTF_FOUND)
	message(FATAL_ERROR "SDL2_ttf library not found")
endif(NOT SDL2_TTF_FOUND)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

find_package(SDL_gfx REQUIRED)
if(NOT SDLGFX_FOUND)
	message(FATAL_ERROR "SDL2_gfx library not found")
endif(NOT SDLGFX_FOUND)
include_directories(${SDLGFX_INCLUDE_DIR})

endif(EMSCRIPTEN)



file(GLOB_RECURSE SOURCES  src/*.cpp)

add_executable(SDLStructured main.cpp ${SOURCES})

if(EMSCRIPTEN)

target_compile_options(SDLStructured PUBLIC -s USE_SDL=2 )
set_target_properties(SDLStructured PROPERTIES LINK_FLAGS "-o index.html -O3 -Os -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=['png'] -s USE_SDL_TTF=2 --embed-file assets -s EXTRA_EXPORTED_RUNTIME_METHODS=['ALLOC_NORMAL','ALLOC_STACK','ALLOC_STATIC','ALLOC_DYNAMIC','ALLOC_NONE']")

else()

target_link_libraries(
  SDLStructured
  ${ZLIB_LIBRARIES}
  ${SDL2_LIBRARY}
  ${SDL2_MIXER_LIBRARIES}
  ${SDL2_IMAGE_LIBRARY}
  ${SDL2_TTF_LIBRARIES}
  ${SDLGFX_LIBRARY}
  )

endif(EMSCRIPTEN)

# Define output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SDLTest_TARGET_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SDLTest_LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SDLTest_LIB_DIR})