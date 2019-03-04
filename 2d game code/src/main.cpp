/* Man Tsz Ho (54394690) */

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")
#pragma comment(lib, "SDL2_ttf.lib")

// include SDL header
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>
#include <math.h>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "..//header/framerate_control.h"

#include "..//header/player.h"
#include "..//header/playerBullet.h"
#include "..//header/enemy.h"
#include"..//header/enemyBullet.h"

//	Define game constant
const int FALSE = 0;
const int TRUE = 1;

const int UP = 3;				// up key
const int DOWN = 2;				// down key
const int LEFT = 1;				// right key
const int RIGHT = 0;			// left key

// Screen dimension
const int SCREEN_WIDTH = 480;			
const int SCREEN_HEIGHT = 640;

// time
Uint32 dwfireDelay = 0;
Uint32 dwenemyFire = 0;
Uint32 dwenemy1GenTime = 0;
Uint32 dwenemy2GenTime = 0;
Uint32 dwisCollided = 0;

int benemyFire = 0;

SDL_Window *gWindow = NULL;			// Global Window Pointer	

// Define local function prototypes
SDL_Surface*	Load_Image(char *szFname);
Mix_Chunk*		Load_Sound(char *szFname);

// score
int iscore = 0;

// Store the value of int for draw to screen
char buffer[50];

// new object
Cplayer playerFighter;

int main(int argc, char *argv[])
{
	// array of objects
	CplayerBullet aplayerBullet[20];	// array of object playerbullet
	Cenemy aenemy1[10];					// array of enemy type 1
	Cenemy aenemy2[10];					// array of enemy type 2
	CenemyBullet aenemyBullet1[500];	// array of enemy bullet type 1
	CenemyBullet aenemyBullet2[500];	// array of enemy bullet type 2

	getTime();

	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();
	TTF_Font* font = TTF_OpenFont(".//font/OpenSans-Regular.ttf", 32);
	SDL_Color foregroundColor = { 100,100, 100 };

	SDL_Surface *pScreen;	// Game primary screen

	SDL_Event event;
	SDL_Rect dest;		// for drawing use

	int bGameStart = FALSE;		// by default game start is false
	int bGamePause = FALSE;		// true if game is pausing
	int bInstruction = FALSE;	// in instruction page
	int bGameover = FALSE;		// game over screen
	int bLoopDone = FALSE;		// true if quit the game loop
	int bisCollided = FALSE;

	int iExplosionAnimFrame = 0;
	int iplayerExplosionAnimFrame = 0;
	int playerFlickerAnimFrame = 0;

	// Initialize SDL Video, Audio and font
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "Error init'ing SDL: %s\n", SDL_GetError());
		exit(1);
	}
	if (TTF_Init < 0)
	{
		fprintf(stderr, "Error init'ing TTF: %s\n", SDL_GetError());
		exit(1);
	}
	if (font == NULL)
	{
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		exit(1);
	}

	// Characer surface
	SDL_Surface *player;			// player image
	SDL_Surface *pplayerBullet;		// player bullet
	SDL_Surface *penemy1;			// enemy type 1
	SDL_Surface *penemy2;			// enemy type 2
	SDL_Surface *penemy1Bullet1;	// enemy bullet type1
	SDL_Surface *penemy1Bullet2;	// enemy bullet type2
	SDL_Surface *penemyBoss;

	SDL_Surface *pbackgroundImg;	// background image

	// pointer to explosion animation
	SDL_Surface *apexplosion[6];
	SDL_Surface *applayerExplosion[6];
	SDL_Surface *applayerFlicker[2];

	// UI image surface
	SDL_Surface *pmenu;
	SDL_Surface *ppause;
	SDL_Surface *pinstruction;
	SDL_Surface *pgameover;

	// Load image
	player = Load_Image(".//image/character/player.png");
	pplayerBullet = Load_Image(".//image/character/player_bullet.png");
	pbackgroundImg = Load_Image(".//image/bg/background.jpg");
	penemy1 = Load_Image(".//image/character/enemy1.png");
	penemy2 = Load_Image(".//image/character/enemy2.png");
	penemy1Bullet1 = Load_Image(".//image/character/enemy_bullet1.png");
	penemy1Bullet2 = Load_Image(".//image/character/enemy_bullet2.png");
	penemyBoss = Load_Image(".//image/character/boss.png");

	// Load explosion image
	apexplosion[0] = Load_Image(".//image/character/explosion_1.png");
	apexplosion[1] = Load_Image(".//image/character/explosion_2.png");
	apexplosion[2] = Load_Image(".//image/character/explosion_3.png");
	apexplosion[3] = Load_Image(".//image/character/explosion_4.png");
	apexplosion[4] = Load_Image(".//image/character/explosion_5.png");
	apexplosion[5] = Load_Image(".//image/character/explosion_6.png");

	applayerExplosion[0] = Load_Image(".//image/character/player_explosion_1.png");
	applayerExplosion[1] = Load_Image(".//image/character/player_explosion_2.png");
	applayerExplosion[2] = Load_Image(".//image/character/player_explosion_3.png");
	applayerExplosion[3] = Load_Image(".//image/character/player_explosion_4.png");
	applayerExplosion[4] = Load_Image(".//image/character/player_explosion_5.png");
	applayerExplosion[5] = Load_Image(".//image/character/player_explosion_6.png");

	applayerFlicker[0] = Load_Image(".//image/character/player_white.png");
	applayerFlicker[1] = Load_Image(".//image/character/player_black.png");

	// Load UI image
	pmenu = Load_Image(".//image/ui/menu.jpg");
	ppause = Load_Image(".//image/ui/pause.png");
	pinstruction = Load_Image(".//image/ui/instruction.jpg");
	pgameover = Load_Image(".//image/ui/gameover.jpg");

	// Create the window : 480 x 640
	gWindow = SDL_CreateWindow("Space Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (gWindow == NULL)
	{
		fprintf(stderr, "Error: Can't open window!  %s\n",
			SDL_GetError());
		exit(1);
	}

	// Setup the primary surface
	pScreen = SDL_GetWindowSurface(gWindow);

	if (pScreen == NULL)
	{
		fprintf(stderr, "Error: Can't open window! %s\n", SDL_GetError());
		exit(1);
	}

	// Initialise the game audio
	if (Mix_OpenAudio(44100, AUDIO_S16, 2, 256) < 0)
	{
		fprintf(stderr, "Error opening audio: %s\n", Mix_GetError());
		exit(1);
	}

	// pointers to game sound
	Mix_Chunk *pstartSound;
	Mix_Chunk *pplayerShootSound;
	Mix_Chunk *phitSound;
	Mix_Chunk *penemyShootSound;
	Mix_Chunk *pplayerHit;

	// load sound
	pstartSound = Mix_LoadWAV(".//sfx/start.wav");
	pplayerShootSound = Mix_LoadWAV(".//sfx/player_shoot.wav");
	phitSound = Mix_LoadWAV(".//sfx/hit.wav");
	penemyShootSound = Mix_LoadWAV(".//sfx/enemy_shoot.wav");
	pplayerHit = Mix_LoadWAV(".//sfx/player_hit.wav");

	Uint32 key; // input key
	int bKeyPressed[4];		// record the arrow key pressed

	float iscrollingOffset = 0;

	// clear the keypress array
	for (int i = 0; i < 4; i++)
		bKeyPressed[i] = FALSE;

	// draw the menu screen
	SDL_BlitSurface(pmenu, NULL, pScreen, NULL);

	do {
		while (SDL_PollEvent(&event) > 0)
		{
			// Keyboard events
			if (event.type == SDL_QUIT)
			{
				// Quit event! (Window close, kill signal, etc.)
				bLoopDone = TRUE;
			}
			// Check for key pressed
			else if (event.type == SDL_KEYDOWN)
			{
				// Check individual key
				key = event.key.keysym.sym;

				if (key == SDLK_ESCAPE)
				{
					// Quit on escape key
					std::cout << bLoopDone << std::endl;
					bLoopDone = TRUE;
				}
				else if (key == SDLK_SPACE) {
					// Start game on space key
					if (!bGameStart) {
						if (bGameover) {
							bGameover = FALSE;

							// initialize level
							iscore = 0;
							playerFighter.setHealth(3);
							playerFighter.setPosX(SCREEN_WIDTH / 2 - 25);
							playerFighter.setPosY(SCREEN_HEIGHT - 80);
							for (int i = 0; i < sizeof(aplayerBullet) / sizeof(*aplayerBullet); i++) {
								aplayerBullet[i].remove();
							}
							for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
								aenemy1[i].remove();
							}
							for (int i = 0; i < sizeof(aenemyBullet1) / sizeof(*aenemyBullet1); i++) {
								aenemyBullet1[i].remove();
							}
							// reset spawn timer
							dwenemy1GenTime = SDL_GetTicks();
							dwenemy2GenTime = SDL_GetTicks();

							// draw the menu screen again
							SDL_BlitSurface(pmenu, NULL, pScreen, NULL);

						}
						else {
							bGameStart = TRUE;
							bInstruction = FALSE;
							
							Mix_PlayChannel(0, pstartSound, 0);
						}
					}
				}
				if (key == SDLK_p) {
					// Pause the game
					if (bGameStart) {
						if (!bGamePause) {
							bGamePause = TRUE;
						}
						else
						{ // Press again to unpause
							bGamePause = FALSE;
							bInstruction = FALSE;
						}
					}
				}
				if (key == SDLK_i) {
					if (!bInstruction) {
						if ((!bGameStart || bGamePause) && !bGameover) {
							bInstruction = TRUE;
						}
					}
					// press again to leave instruction page
					else {
						bInstruction = FALSE;
						if (!bGameStart) {
							// draw the menu screen again if game haven't start
							SDL_BlitSurface(pmenu, NULL, pScreen, NULL);

						}
					}
				}
				else if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT)
				{
					// record the key stroke
					bKeyPressed[(int)(key - SDLK_RIGHT)] = TRUE;
				}
			}
				// Check for key released
				if (event.type == SDL_KEYUP)
				{
					key = event.key.keysym.sym;

					if (key == SDLK_UP || key == SDLK_DOWN || key == SDLK_RIGHT || key == SDLK_LEFT)
					{
						// record the key stroke
						bKeyPressed[(int)(key - SDLK_RIGHT)] = FALSE;
					}
				}
		}
		if (bInstruction) {
			SDL_BlitSurface(pinstruction, NULL, pScreen, NULL);
		}

		if (bGameStart) {
			// Redraw the whole screen with gray color
			SDL_FillRect(pScreen, NULL, SDL_MapRGB(pScreen->format, 128, 128, 128));

			if (!bGamePause) {
				// move player
				if (bKeyPressed[UP])
				{
					playerFighter.moveUp();
				}
				if (bKeyPressed[DOWN])
				{
					playerFighter.moveDown();
				}
				if (bKeyPressed[RIGHT])
				{
					playerFighter.moveRight();
				}
				if (bKeyPressed[LEFT])
				{
					playerFighter.moveLeft();
				}
			}

			// draw background
			if (pbackgroundImg == NULL) {
				std::cout << "NULL pointer of pbackgroundImg" << std::endl;
			}
			else {
				if (!bGamePause)
					//Scroll background
					iscrollingOffset += 0.5;

				if (iscrollingOffset > 300)
					iscrollingOffset = 0;
				dest.x = 0;
				dest.y = 0;

				SDL_Rect srect;
				srect.x = 0;
				srect.y = round(640 - iscrollingOffset);
				srect.w = 480;
				srect.h = 640;

				SDL_BlitSurface(pbackgroundImg, &srect, pScreen, &dest);
			}

			if (player == NULL) {
				std::cout << "NULL pointer of player" << std::endl;
			}
			else {
				// draw fighter
				dest.x = playerFighter.getPosX();
				dest.y = playerFighter.getPosY();

				SDL_BlitSurface(player, NULL, pScreen, &dest);
			}

			// check fire delay
			if (SDL_GetTicks() - dwfireDelay > 100 && !bGamePause) {
				for (int i = 0; i < sizeof(aplayerBullet) / sizeof(*aplayerBullet); i += 2) {
					if (aplayerBullet[i].getValid() == 0 && aplayerBullet[i + 1].getValid() == 0) {
						aplayerBullet[i].setValid(1);
						aplayerBullet[i].setPosX(playerFighter.getPosX() + 10);
						aplayerBullet[i].setPosY(playerFighter.getPosY());

						aplayerBullet[i + 1].setValid(1);
						aplayerBullet[i + 1].setPosX(playerFighter.getPosX() + 30);
						aplayerBullet[i + 1].setPosY(playerFighter.getPosY());

						break;
					}
					Mix_PlayChannel(1, pplayerShootSound, 0);
				}
				dwfireDelay = SDL_GetTicks(); // reset fire delay
			}

			// check every bullets
			for (int i = 0; i < sizeof(aplayerBullet) / sizeof(*aplayerBullet); i++) {
				if (bGamePause && aplayerBullet[i].getValid() == 1) {
					// stop bullets when game pause
					aplayerBullet[i].stop();
				}
				else { // shoot new bullet
					if (aplayerBullet[i].getValid() == 1)
						// move bullet
						aplayerBullet[i].move();
					}

					// get position
					dest.x = aplayerBullet[i].getPosX();
					dest.y = aplayerBullet[i].getPosY();

					// draw
					SDL_BlitSurface(pplayerBullet, NULL, pScreen, &dest);
			}

			// Create new enemy 1
			if ((SDL_GetTicks() - dwenemy1GenTime > 1000) && !bGamePause) { // wait 1 sec
				for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
					if (aenemy1[i].getHit() == 0 && aenemy1[i].getValid() == 0) {
						aenemy1[i].create(rand() % 400 + 40, -20);
						dwenemy1GenTime = SDL_GetTicks(); // reset timer
						break;
					}
				}
			}

			// move enemy1
			for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
				if (aenemy1[i].getValid() == 1) {
					if (bGamePause) {
						// stop enemy when game pause
						aenemy1[i].stop();
					}
					else {
						// move enemy
						aenemy1[i].move1();
					}
					// get position
					dest.x = aenemy1[i].getPosX();
					dest.y = aenemy1[i].getPosY();

					// draw
					SDL_BlitSurface(penemy1, NULL, pScreen, &dest);
				}
			}

			// Create new enemy 2
			if ((SDL_GetTicks() - dwenemy2GenTime > 3000) && !bGamePause) { // wait 1 sec
				for (int i = 0; i < sizeof(aenemy2) / sizeof(*aenemy2); i++) {
					if (aenemy2[i].getHit() == 0 && aenemy2[i].getValid() == 0) {
						aenemy2[i].create(rand() % 400 + 40, 690);
						dwenemy2GenTime = SDL_GetTicks(); // reset timer
						break;
					}
				}
			}

			// move enemy2
			for (int i = 0; i < sizeof(aenemy2) / sizeof(*aenemy2); i++) {
				if (aenemy2[i].getValid() == 1) {
					if (bGamePause) {
						// stop enemy when game pause
						aenemy2[i].stop();
					}
					else {
						// move enemy
						aenemy2[i].move2();
					}
					// get position
					dest.x = aenemy2[i].getPosX();
					dest.y = aenemy2[i].getPosY();

					// draw
					SDL_BlitSurface(penemy2, NULL, pScreen, &dest);
				}
			}


			// enemy shoot
			for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
				if (aenemy1[i].getFired() == 0 && aenemy1[i].getPosY() > SCREEN_HEIGHT - 200 - (rand() % 300)) {
					for (int j = 0; j < 36; j++) { // set angle
						for (int k = 0; k < sizeof(aenemyBullet1) / sizeof(*aenemyBullet1); k++) { // new bullets
							if (aenemyBullet1[k].getValid() == 0) { // set bullet
								aenemyBullet1[k].create(aenemy1[i].getPosX() + 25, aenemy1[i].getPosY() + 25);

								aenemyBullet1[k].setAngle(j * 10);
								aenemy1[i].setFired(1);
								break;
							}
							Mix_PlayChannel(2, penemyShootSound, 0);
						}
					}
				}
			}

			// moving enemy bullets
			for (int i = 0; i < sizeof(aenemyBullet1) / sizeof(*aenemyBullet1); i++) {
				if (aenemyBullet1[i].getValid() == 1) {
					if (bGamePause) {
						aenemyBullet1[i].stop();
					}
					else {
						// shoot
						aenemyBullet1[i].shoot1();
					}
					// get position
					dest.x = aenemyBullet1[i].getDestX();
					dest.y = aenemyBullet1[i].getDestY();

					// draw
					SDL_BlitSurface(penemy1Bullet1, NULL, pScreen, &dest);
				}
			}

			for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
				if (aenemy1[i].getPosY() ==200) {
					for (int j = 0; j < 5; j++) {
						for (int k = 0; k < sizeof(aenemyBullet2) / sizeof(*aenemyBullet2); k++) { // new bullets
							if (aenemyBullet2[k].getValid() == 0) { // set bullet
								aenemyBullet2[k].create(aenemy1[i].getPosX() - 25 + j * 30, aenemy1[i].getPosY() + 25);

								break;
							}
							Mix_PlayChannel(2, penemyShootSound, 0);
						}
					}
				}
			}

			// moving enemy bullets
			for (int i = 0; i < sizeof(aenemyBullet2) / sizeof(*aenemyBullet2); i++) {
				if (aenemyBullet2[i].getValid() == 1) {
					if (bGamePause) {
						aenemyBullet2[i].stop();
					}
					else {
						// shoot
						aenemyBullet2[i].shoot2();
					}
					// get position
					dest.x = aenemyBullet2[i].getDestX();
					dest.y = aenemyBullet2[i].getDestY();

					// draw
					SDL_BlitSurface(penemy1Bullet2, NULL, pScreen, &dest);
				}
			}

			// player can be hit again
			if (SDL_GetTicks() - dwisCollided > 2000 && !bGamePause)
				bisCollided = FALSE;

			// check collision - playerBullet and enemy 1
			for (int i = 0; i < sizeof(aplayerBullet) / sizeof(*aplayerBullet); i++) {
				if (aplayerBullet[i].getValid() == 1) {
					for (int j = 0; j < sizeof(aenemy1) / sizeof(*aenemy1); j++) {
						if (aenemy1[j].getValid() == 1
							&& aenemy1[j].getPosX() < aplayerBullet[i].getPosX() + 5	// left1 < right2
							&& aenemy1[j].getPosX() + 50 > aplayerBullet[i].getPosX()	// right1 > left2
							&& aenemy1[j].getPosY() < aplayerBullet[i].getPosY() + 15	// top1 < bottom2
							&& aenemy1[j].getPosY() + 50 > aplayerBullet[i].getPosY())	// bottom1 > top2
						{
							aplayerBullet[i].remove();
							aenemy1[j].setValid(0);
							aenemy1[j].setHit(1);
							iscore += 100;

							Mix_PlayChannel(0, phitSound, 0);
						}
					}
				}
			}

			// check collision - playerBullet and enemy 2
			for (int i = 0; i < sizeof(aplayerBullet) / sizeof(*aplayerBullet); i++) {
				if (aplayerBullet[i].getValid() == 1) {
					for (int j = 0; j < sizeof(aenemy2) / sizeof(*aenemy2); j++) {
						if (aenemy2[j].getValid() == 1
							&& aenemy2[j].getPosX() < aplayerBullet[i].getPosX() + 5
							&& aenemy2[j].getPosX() + 50 > aplayerBullet[i].getPosX()
							&& aenemy2[j].getPosY() < aplayerBullet[i].getPosY() + 15
							&& aenemy2[j].getPosY() + 24 > aplayerBullet[i].getPosY())
						{
							aplayerBullet[i].remove();
							aenemy2[j].setValid(0);
							aenemy2[j].setHit(1);
							iscore += 200;

							Mix_PlayChannel(0, phitSound, 0);
						}
					}
				}
			}

			// check collision - enemy 1 and player
			for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
				if (aenemy1[i].getValid() == 1 && !bisCollided
					&& aenemy1[i].getPosX() < playerFighter.getPosX() + 45
					&& aenemy1[i].getPosX() + 50 > playerFighter.getPosX()
					&& aenemy1[i].getPosY() < playerFighter.getPosY() + 45
					&& aenemy1[i].getPosY() + 50 > playerFighter.getPosY())
				{
					playerFighter.setHit(1);
					playerFighter.setHealth(playerFighter.getHealth() - 1);
					dwisCollided = SDL_GetTicks();
					bisCollided = TRUE;
					Mix_PlayChannel(0, pplayerHit, 0);
				}
			}

			// check collision - enemy 2 and player
			for (int i = 0; i < sizeof(aenemy2) / sizeof(*aenemy2); i++) {
				if (aenemy2[i].getValid() == 1 && !bisCollided
					&& aenemy2[i].getPosX() < playerFighter.getPosX() + 45
					&& aenemy2[i].getPosX() + 50 > playerFighter.getPosX()
					&& aenemy2[i].getPosY() < playerFighter.getPosY() + 45
					&& aenemy2[i].getPosY() + 24 > playerFighter.getPosY())
				{
					playerFighter.setHit(1);
					playerFighter.setHealth(playerFighter.getHealth() - 1);
					dwisCollided = SDL_GetTicks();
					bisCollided = TRUE;
					Mix_PlayChannel(0, pplayerHit, 0);
				}
			}

			// check collision - enemy bullet 1 and player
			for (int i = 0; i < sizeof(aenemyBullet1) / sizeof(*aenemyBullet1); i++) {
				int x = pow(((aenemyBullet1[i].getDestX() + 5) - (playerFighter.getPosX() + 24)), 2);
				int y = pow(((aenemyBullet1[i].getDestY() + 5) - (playerFighter.getPosY() + 35)), 2);

				if ((x + y) < pow(10, 2) && (aenemyBullet1[i].getValid() == 1 && !bisCollided)) {
					playerFighter.setHit(1);
					playerFighter.setHealth(playerFighter.getHealth() - 1);
					dwisCollided = SDL_GetTicks();
					aenemyBullet1[i].setValid(0);
					bisCollided = TRUE;
					Mix_PlayChannel(0, pplayerHit, 0);
				}
			}

			// check collision - enemy bullet 2 and player
			for (int i = 0; i < sizeof(aenemyBullet2) / sizeof(*aenemyBullet2); i++) {
				if (!bisCollided && aenemyBullet2[i].getValid() == 1
					&& aenemyBullet2[i].getDestX() < playerFighter.getPosX() + 40
					&& aenemyBullet2[i].getDestX() + 10 > playerFighter.getPosX()
					&& aenemyBullet2[i].getDestY() < playerFighter.getPosY() + 40
					&& aenemyBullet2[i].getDestY() + 20 > playerFighter.getPosY())
				{
					playerFighter.setHit(1);
					playerFighter.setHealth(playerFighter.getHealth() - 1);
					dwisCollided = SDL_GetTicks();
					aenemyBullet2[i].setValid(0);
					bisCollided = TRUE;
					Mix_PlayChannel(0, pplayerHit, 0);
				}
			}

			// draw enemy 1 explosion
			for (int i = 0; i < sizeof(aenemy1) / sizeof(*aenemy1); i++) {
				if (aenemy1[i].getHit() == 1) {
					// get the explosion position and draw it
					dest.x = aenemy1[i].getPosX();
					dest.y = aenemy1[i].getPosY();
					SDL_BlitSurface(apexplosion[iExplosionAnimFrame], NULL, pScreen, &dest);
					
					// draw a new frame every 0.2s
					if(SDL_GetTicks() % 20 == 0 && !bGamePause)
						iExplosionAnimFrame++;

					// reset
					if (iExplosionAnimFrame == 5) {
						aenemy1[i].setHit(0);
						iExplosionAnimFrame = 0;
					}
				}
			}

			// draw enemy 2 explosion
			for (int i = 0; i < sizeof(aenemy2) / sizeof(*aenemy2); i++) {
				if (aenemy2[i].getHit() == 1) {
					// get the explosion position and draw it
					dest.x = aenemy2[i].getPosX();
					dest.y = aenemy2[i].getPosY();
					SDL_BlitSurface(apexplosion[iExplosionAnimFrame], NULL, pScreen, &dest);

					// draw a new frame every 0.2s
					if (SDL_GetTicks() % 20 == 0 && !bGamePause)
						iExplosionAnimFrame++;

					// reset
					if (iExplosionAnimFrame == 5) {
						aenemy2[i].setHit(0);
						iExplosionAnimFrame = 0;
					}
				}
			}


			dest.x = SCREEN_WIDTH / 2 - 100;
			dest.y = 20;
			SDL_BlitSurface(penemyBoss, NULL, pScreen, &dest);

			if (bisCollided) {
				dest.x = playerFighter.getPosX();
				dest.y = playerFighter.getPosY();

				// player flicker
				SDL_BlitSurface(applayerFlicker[playerFlickerAnimFrame], NULL, pScreen, &dest);
				playerFlickerAnimFrame++;
				playerFlickerAnimFrame = playerFlickerAnimFrame % 2;

				// draw explosion
				if (playerFighter.getHit() == 1) {
					SDL_BlitSurface(applayerExplosion[iplayerExplosionAnimFrame], NULL, pScreen, &dest);

					// draw a new frame every 0.2s
					if (SDL_GetTicks() % 15 == 0 && !bGamePause)
						iplayerExplosionAnimFrame++;

					// reset
					if (iplayerExplosionAnimFrame == 5) {
						playerFighter.setHit(0);
						iplayerExplosionAnimFrame = 0;
					}
				}
			}

			// Draw UI
			sprintf_s(buffer, "%d", iscore); // Convert iScore from int to const char
			SDL_Surface* puiDisplay = TTF_RenderText_Solid(font, buffer, foregroundColor);
			dest.x = 30;
			dest.y = 20;
			SDL_BlitSurface(puiDisplay, NULL, pScreen, &dest);
			SDL_FreeSurface(puiDisplay);

			sprintf_s(buffer, "%d", playerFighter.getHealth()); // Convert playerFighter.getHealth() from int to const char
			puiDisplay = TTF_RenderText_Solid(font, buffer, foregroundColor);
			dest.x = 400;
			dest.y = 580;
			SDL_BlitSurface(puiDisplay, NULL, pScreen, &dest);
			SDL_FreeSurface(puiDisplay);


			if (bGamePause) {
				SDL_BlitSurface(ppause, NULL, pScreen, NULL);
				if (bInstruction) {
					SDL_BlitSurface(pinstruction, NULL, pScreen, NULL);
				}
			}
		} // end of bgamestart

		// Update the display
		SDL_UpdateWindowSurface(gWindow);

		// Keep the game on 60fps
		framerateControl();

		// game over
		if (playerFighter.getHealth() < 0) {
			SDL_BlitSurface(pgameover, NULL, pScreen, NULL);
			sprintf_s(buffer, "%d", iscore); // Convert iScore from int to const char
			SDL_Surface* puiDisplay = TTF_RenderText_Solid(font, buffer, foregroundColor);
			dest.x = 220;
			dest.y = 330;
			SDL_BlitSurface(puiDisplay, NULL, pScreen, &dest);
			SDL_FreeSurface(puiDisplay);

			bGameStart = FALSE;
			bGameover = TRUE;
		}
	}
	 while (!bLoopDone);

	// free and close SDL
	SDL_FreeSurface(player);
	SDL_FreeSurface(pplayerBullet);
	SDL_FreeSurface(penemy1);
	SDL_FreeSurface(penemy2);
	SDL_FreeSurface(penemyBoss);

	TTF_CloseFont(font);

	SDL_FreeSurface(pmenu);
	SDL_FreeSurface(pinstruction);
	SDL_FreeSurface(ppause);
	SDL_FreeSurface(pgameover);

	Mix_FreeChunk(pstartSound);
	Mix_FreeChunk(pplayerShootSound);
	Mix_FreeChunk(phitSound);
	Mix_FreeChunk(penemyShootSound);
	Mix_FreeChunk(pplayerHit);

	SDL_DestroyWindow(gWindow);
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();

	return(0);
}

//	Load_Image() - load an image, abort if error.
SDL_Surface* Load_Image(char *szFname)
{
	SDL_Surface *pSurface = NULL;

	pSurface = IMG_Load(szFname);

	if (pSurface == NULL)
	{
		fprintf(stderr, "Error loading image %s: %s\n", szFname, IMG_GetError());
		exit(1);
	}

	return pSurface;
}

//	Load_Sound() - Load a wav sound file, abort if fail.
Mix_Chunk* Load_Sound(char *szFname)
{
	Mix_Chunk *pChunk = NULL;

	pChunk = Mix_LoadWAV(szFname);

	if (pChunk == NULL)
	{
		fprintf(stderr, "Error loading sound %s: %s\n", szFname, Mix_GetError());
		exit(1);
	}

	return pChunk;
}
