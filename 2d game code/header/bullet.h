// Man Tsz Ho (54394690) //

#ifndef BULLET_H
#define BULLET_H

class Cbullet
{
protected:
	int iposX;
	int iposY;

public:
	Cbullet();
	~Cbullet();

	void setPosX(int iposX);
	void setPosY(int iposY);

	int getPosX();
	int getPosY();
};

#endif