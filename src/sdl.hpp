#ifndef SDL_H
#define SDL_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "SDL2_gfxPrimitives.h"
#include <string>

#define UNUSED(x) ((void)(x))

namespace SDL
{
	/// Starts SDL2, MUST be called before everything else.
	bool init();

	/// Destroys SDL2, MUST be called when program ends.
	void exit();
};


#endif // !SDL_H
