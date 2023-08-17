#include "texture.h"

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename, int* TEXTURE_W, int* TEXTURE_H)
{
	SDL_Texture* img = IMG_LoadTexture(renderer, filename);	
	SDL_QueryTexture(img, NULL, NULL, TEXTURE_W, TEXTURE_H);
	return img;
}