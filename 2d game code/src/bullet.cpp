// Man Tsz Ho (54394690) //

// include SDL header
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "../header/bullet.h"

Cbullet::Cbullet()
{
}

Cbullet::~Cbullet()
{
}

void Cbullet::setPosX(int ibulletPosX) {
	iposX = ibulletPosX;
}
void Cbullet::setPosY(int ibulletPosY) {
	iposY = ibulletPosY;
}

int Cbullet::getPosX() {
	return	iposX;
}
int Cbullet::getPosY() {
	return iposY;
}
