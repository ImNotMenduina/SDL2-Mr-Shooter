#ifndef structus_H
#define structus_H
#include<SDL.h>

typedef struct
{
	SDL_Texture* RUNhero;
	SDL_Texture* IDLEhero;
	SDL_Texture* FIREhero;
	SDL_Texture* FIREUPhero;
	SDL_Texture* JUMPhero;
	SDL_Texture* DEADhero;
	SDL_Rect heroFrames[30];
}HEROsprites;

 struct enemySprites
{
	SDL_Texture* RUNenemy;
	SDL_Texture* IDLEenemy;
	SDL_Texture* SHOOTenemy;
	SDL_Texture* DEADhero;
	SDL_Rect enemyFrames[17];
};
 typedef struct enemySprites ENEMYsprites;


typedef struct
{
	int speedx;
	int speedy;
}SPEED;

typedef struct
{
	int x, y; 
	int r;
}CIRCLE;

#endif