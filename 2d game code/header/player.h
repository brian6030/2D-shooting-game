// Man Tsz Ho (54394690) //

#ifndef PLAYER_H
#define PLAYER_H

class Cplayer {
private:
	int ihealth;
	int iposX;
	int iposY;
	int ispeedH; // move horizontal
	int ispeedV; //move vertical
	int bhit;

public:
	Cplayer();
	~Cplayer();

	//bool bisCollided = 0;
	void setHealth(int ihealth);
	void setPosX(int iposX);
	void setPosY(int iposY);
	void setHit(int bhit);

	int getHealth();
	int getPosX();
	int getPosY();
	int getHit();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
};

#endif