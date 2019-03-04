// Man Tsz Ho (54394690) //

#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "../header/bullet.h"

class CenemyBullet : public Cbullet
{
private:
	double ispeed;

	int bvalid;
	int iangle;

	int idestX;
	int idestY;

public:
	CenemyBullet();
	~CenemyBullet();

	void setSpeed(float ispeed);
	void setValid(int bvalid);
	void setAngle(int iangle);
	void setDestX(int idestPosX);
	void setDestY(int idestPosY);

	int getSpeed();
	int getValid();

	int getDestX();
	int getDestY();

	float radian(int degree); // convert degree to radian
	void shoot1();
	void shoot2();

	void remove();

	void stop();

	void create(int posX, int posY);
};

#endif