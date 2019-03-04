#include "..//header/player.h"

const int PLAYER_IMAGE_SIZE = 60;

int screen_width = 480;
int screen_height = 640;

Cplayer::Cplayer() :
	ihealth(3),
	iposX(screen_width / 2 - PLAYER_IMAGE_SIZE / 2),
	iposY(screen_height - 80),
	ispeedH(1),
	ispeedV(1),
	bhit(0)
{}
Cplayer::~Cplayer() {}

//setter
void Cplayer::setHealth(int iplayerHealth) {
	ihealth = iplayerHealth;
}
void Cplayer::setPosX(int iplayerPosX) {
	iposX = iplayerPosX;
}
void Cplayer::setPosY(int iplayerPosY) {
	iposY = iplayerPosY;
}
void Cplayer::setHit(int bplayerHit) {
	bhit = bplayerHit;
}

//getter
int Cplayer::getHealth() {
	return ihealth;
}
int Cplayer::getPosX() {
	return	iposX;
}
int Cplayer::getPosY() {
	return iposY;
}
int Cplayer::getHit() {
	return bhit;
}

void Cplayer::moveUp() {
	iposY -= ispeedV;

	// avoid leaving the screen
	if (iposY < 0) {
		iposY = 0;
	}
}
void Cplayer::moveDown() {
	iposY += ispeedV;

	// avoid leaving the screen
	if (iposY >(screen_height - PLAYER_IMAGE_SIZE)) {
		iposY = screen_height - PLAYER_IMAGE_SIZE;
	}
}
void Cplayer::moveLeft() {
	iposX -= ispeedH;

	// avoid leaving the screen
	if (iposX < 0) {
		iposX = 0;
	}
}
void Cplayer::moveRight() {
	iposX += ispeedH;

	// avoid leaving the screen
	if (iposX >(screen_width - PLAYER_IMAGE_SIZE)) {
		iposX = screen_width - PLAYER_IMAGE_SIZE;
	}
}
