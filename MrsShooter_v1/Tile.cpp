#include "Tile.h"
using namespace TileClass;

Tile::Tile(int posx, int posy, SDL_Renderer* renderer)
{
	this->posx = posx;
	this->posy = posy;
	this->on = false;
	initTile(renderer);
}


void Tile::initTile(SDL_Renderer* renderer)
{
	int TEXTURE_W, TEXTURE_H;
	this->tileTexture = loadTexture(renderer, "maps/tiles_out.png", &TEXTURE_W, &TEXTURE_H);

	if (this->tileTexture == NULL)
		std::cout << "deu merda";

	SDL_Rect  collisor;
	collisor.x = posx;
	collisor.y = posy;
	collisor.w = 16;
	collisor.h = 16;
	this->tileBox = collisor;

	SDL_Rect  tilePrint;
	tilePrint.x = 10 * 16;
	tilePrint.y = 2 * 16;
	tilePrint.w = 16;
	tilePrint.h = 16;
	this->tilePrint = tilePrint;
	
}

void Tile::UpdateTile(SDL_Renderer* renderer, SDL_Rect print)
{
	SDL_RenderCopy(renderer, this->tileTexture, &this->tilePrint, &print);
}

SDL_Texture* Tile::getTileTexture()
{
	return this->tileTexture;
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

bool Tile::getOn()
{
	return this->on;
}

void Tile::setOn(bool on)
{
	this->on = on;
}

