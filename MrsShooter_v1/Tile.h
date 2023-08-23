#ifndef Tile_H
#define Tile_H
#include <iostream>
#include <SDL.h>
#include "texture.h"
namespace TileClass
{
	class Tile 
	{
	private:
		int posx;
		int posy; 
		int type;
		SDL_Rect tileBox;
		SDL_Rect tilePrint;
		SDL_Texture* tileTexture;
	public:
		Tile(int posx, int posy, int type, SDL_Renderer* renderer);

		void initTile(SDL_Renderer* renderer);

		void UpdateTile(SDL_Renderer* renderer, SDL_Rect print);

		int getPosY();

		int getPosX();

		SDL_Rect getTilePrint();

		SDL_Rect getTileBox();

		int getType();
	};
}

#endif