// Man Tsz Ho (54394690) //

#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class Cenemy
{
private:
	int iposX;
	int iposY;
	int ispeed;
	int bvalid;
	int bfired;
	int bhit;

public:
	Cenemy();
	~Cenemy();

	void setPosX(int iposX);
	void setPosY(int iposY);
	void setSpeed(int ispeed);
	void setValid(int bvalid);
	void setFired(int bfired);
	void setHit(int bhit);

	int getPosX();
	int getPosY();
	int getSpeed();
	int getValid();
	int getFired();
	int getHit();

	void move1();
	void move2();
	void stop();
	void remove();
	void create(int posX, int posY);
};

#endif