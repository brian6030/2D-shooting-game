// Man Tsz Ho (54394690) //

// include SDL header
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

Uint32 dwStartTime;		// start time
Uint32 dwEndTime;		// end time

void getTime() {
	dwStartTime = SDL_GetTicks();
}

// Pause at the end if necessary to control the frame rate
void framerateControl() {
	dwEndTime = SDL_GetTicks();
	if (dwEndTime < dwStartTime + (1000 / 60))
	{
		SDL_Delay(dwStartTime + (1000 / 60) - dwEndTime);
	}
}
