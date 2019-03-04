// Man Tsz Ho (54394690) //

#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "../header/bullet.h"

class CplayerBullet :public Cbullet
{
private:
	//int iposX;
	//int iposY;
	int ispeed;
	int bvalid;

public:
	CplayerBullet();
	~CplayerBullet();

	void setSpeed(int ispeed);
	void setValid(int bvalid);

	int getSpeed();
	int getValid();

	void move();
	void stop();
	void remove();
};

#endif