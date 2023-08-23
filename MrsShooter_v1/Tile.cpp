#include "Tile.h"
using namespace TileClass;

int TEXTURE_W, TEXTURE_H;

Tile::Tile(int posy, int posx, int type, SDL_Renderer* renderer)
{
	this->posy = posy;
	this->posx = posx;
	this->type = type;
	initTile(renderer);
}


void Tile::initTile(SDL_Renderer* renderer)
{
	int a, b;
	this->tileTexture = loadTexture(renderer, "maps/tiles_out.png", &a, &b);

	SDL_Rect  collisor;
	collisor.x = posx;
	collisor.y = posy;
	collisor.w = 16;
	collisor.h = 16;
	this->tileBox = collisor;

	if(this->type == 59)
	{
		SDL_Rect  tilePrint;
		tilePrint.x = 10 * 16;
		tilePrint.y = 2 * 16;
		tilePrint.w = 16;
		tilePrint.h = 16;
		this->tilePrint = tilePrint;
	}
	else if (this->type == 150)
	{
		SDL_Rect  tilePrint;
		tilePrint.x = 7 * 16;
		tilePrint.y = 11 * 16;
		tilePrint.w = 16;
		tilePrint.h = 16;
		this->tilePrint = tilePrint;
	}
	else if (this->type == 151)
	{
		SDL_Rect  tilePrint;
		tilePrint.x = 8 * 16;
		tilePrint.y = 11 * 16;
		tilePrint.w = 16;
		tilePrint.h = 16;
		this->tilePrint = tilePrint;
	}
	else if (this->type == 163)
	{
		SDL_Rect  tilePrint;
		tilePrint.x = 7 * 16;
		tilePrint.y = 12 * 16;
		tilePrint.w = 16;
		tilePrint.h = 16;
		this->tilePrint = tilePrint;
	}
	else if (this->type == 164)
	{
		SDL_Rect  tilePrint;
		tilePrint.x = 8 * 16;
		tilePrint.y = 12 * 16;
		tilePrint.w = 16;
		tilePrint.h = 16;
		this->tilePrint = tilePrint;
	}
}

void Tile::UpdateTile(SDL_Renderer* renderer, SDL_Rect print)
{
	SDL_RenderCopy(renderer, this->tileTexture, &this->tilePrint, &print);
	////
	///// HERO TILE COLLIDER
	SDL_SetRenderDrawColor(renderer, 250, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &print);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	/////
	////
}

SDL_Rect Tile::getTilePrint()
{
	return this->tilePrint;
}

SDL_Rect Tile::getTileBox()
{
	return this->tileBox;
}

int Tile::getPosY()
{
	return this->posy;
}

int Tile::getPosX()
{
	return this->posx;
}

int Tile::getType()
{
	return this->type;
}