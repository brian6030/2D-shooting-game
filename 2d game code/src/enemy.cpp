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

#include "../header/enemy.h"

Cenemy::Cenemy()
{
	setPosX(iposX);
	setPosY(-20);
	setSpeed(2);
	setValid(0);
	bfired = 0;
	bhit = 0;
}

Cenemy::~Cenemy()
{
}

//setter
void Cenemy::setPosX(int ienemyPosX) {
	iposX = ienemyPosX;
}
void Cenemy::setPosY(int ienemyPosY) {
	iposY = ienemyPosY;
}
void Cenemy::setSpeed(int ienemySpeed) {
	ispeed = ienemySpeed;
}
void Cenemy::setValid(int benemyValid) {
	bvalid = benemyValid;
}
void Cenemy::setFired(int benemyfired) {
	bfired = benemyfired;
}
void Cenemy::setHit(int benemyHit) {
	bhit = benemyHit;
}

//getter
int Cenemy::getPosX() {
	return	iposX;
}
int Cenemy::getPosY() {
	return iposY;
}
int Cenemy::getSpeed() {
	return ispeed;
}
int Cenemy::getValid() {
	return bvalid;
}
int Cenemy::getFired() {
	return bfired;
}
int Cenemy::getHit() {
	return bhit;
}

void Cenemy::move1() {
	if (iposY < 640) {
		ispeed = 1;
		iposY += ispeed;
	}
	else
		remove();
}

void Cenemy::move2() {
	if (iposY > -30) {
		ispeed = 2;
		iposY -= ispeed;
	}
	else
		remove();
}

void Cenemy::stop() {
	ispeed = 0;
}

void Cenemy::remove() {
	bvalid = 0;
	iposX = -100;
	iposY = -100;
}

void Cenemy::create(int posX, int posY) {
	bvalid = 1;
	iposX = posX;
	iposY = posY;
	bfired = 0;
}