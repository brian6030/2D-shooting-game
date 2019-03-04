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

#include "../header/playerBullet.h"
#include "../header/bullet.h"

CplayerBullet::CplayerBullet()
{
	bvalid = 0;
}

CplayerBullet::~CplayerBullet()
{
}

//setter
void CplayerBullet::setSpeed(int ibulletSpeed) {
	ispeed = ibulletSpeed;
}
void CplayerBullet::setValid(int bbulletValid) {
	bvalid = bbulletValid;
}

//getter
int CplayerBullet::getSpeed() {
	return ispeed;
}
int CplayerBullet::getValid() {
	return bvalid;
}

void CplayerBullet::move() {
	ispeed = 3;
	if (iposY > -30) {
		iposY -= ispeed;
	}
	else {
		remove();
	}

}

void CplayerBullet::stop() {
	ispeed = 0;
}

void CplayerBullet::remove() {
	bvalid = 0;
	iposX = -20;
	iposY = -20;
}
