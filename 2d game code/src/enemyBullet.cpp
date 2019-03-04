// Man Tsz Ho (54394690) //

#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <math.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "../header/enemyBullet.h"
#include "../header/bullet.h"

CenemyBullet::CenemyBullet()
{
	ispeed = 0;
	bvalid = 0;
	idestX = 0;
	idestY = 0;
}

CenemyBullet::~CenemyBullet()
{
}

//setter
void CenemyBullet::setSpeed(float ibulletSpeed) {
	ispeed = ibulletSpeed;
}
void CenemyBullet::setValid(int bbulletValid) {
	bvalid = bbulletValid;
}
void CenemyBullet::setAngle(int ibulletAngle) {
	iangle = ibulletAngle;
}
void CenemyBullet::setDestX(int idestPosX) {
	idestX = idestPosX;
}
void CenemyBullet::setDestY(int idestPosY) {
	idestY = idestPosY;
}


//getter
int CenemyBullet::getSpeed() {
	return ispeed;
}
int CenemyBullet::getValid() {
	return bvalid;
}
int CenemyBullet::getDestX() {
	return idestX;
}
int CenemyBullet::getDestY() {
	return idestY;
}

float CenemyBullet::radian(int degree) {
	return degree * 180 / M_PI;
}

void CenemyBullet::shoot1() {
	ispeed += 0.4;
	if (idestX < -10 || idestX > 485 || idestY < -10 || idestY > 645) {
		remove();
	}
	else {
		idestX = iposX + ispeed * cos(radian(iangle));
		idestY = iposY + ispeed * sin(radian(iangle));
	}
}

void CenemyBullet::shoot2() {
	ispeed += 2;
	if (idestX < -10 || idestX > 485 || idestY < -10 || idestY > 645) {
		remove();
	}
	else {
		idestX = iposX;
		idestY = iposY + ispeed;
	}

}

void CenemyBullet::remove() {
	bvalid = 0;
	ispeed = 0;
	idestX = -9;
	idestY = -9;
}

void CenemyBullet::stop() {
	idestX = iposX + ispeed * cos(radian(iangle));
	idestY = iposY + ispeed * sin(radian(iangle));
}

void CenemyBullet::create(int posX, int posY) {
	bvalid = 1;
	iposX = posX;
	iposY = posY;
}