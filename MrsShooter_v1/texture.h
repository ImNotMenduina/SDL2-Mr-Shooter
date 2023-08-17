#ifndef texture_H
#define texture_H
#include<SDL.h>
#include<SDL_image.h>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filename, int* TEXTURE_W, int* TEXTURE_H);

#endif

