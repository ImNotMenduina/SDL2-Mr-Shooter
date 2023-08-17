#ifndef Tile_H
#define Tile_H
#include <iostream>
#include <SDL.h>
#include "texture.h"
namespace TILES
{
	class Tile 
	{
	private:
		int posx;
		int posy; 
		bool on;
		SDL_Rect tileBox;
		SDL_Rect tilePrint;
		SDL_Texture* tileTexture;
	public:
		Tile(int posx, int posy, SDL_Renderer* renderer);

		void initTile(SDL_Renderer* renderer);

		void UpdateTile(SDL_Renderer* renderer, SDL_Rect print);

		bool getOn();

		void setOn(bool on);

		int getPosY();

		SDL_Rect getTilePrint();

		SDL_Rect getTileBox();

		SDL_Texture* getTileTexture();
	};
}

#endif