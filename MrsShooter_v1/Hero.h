#ifndef Hero_H
#define Hero_H
#define HERO_RUN_AND_GUN 12
#include <SDL.h>
#include <SDL_image.h>
#include "structus.h"
#include "Enemy.h"
#include "texture.h"

namespace HeroClass
{
	class Hero
	{
	private:
		int life;
		int posx;
		int posy;
		int direction;
		bool onTheFloor;
		SPEED heroVelocity;
		HEROsprites moveHero;
		SDL_Rect heroBox;
	public:
		Hero(int posx, int posy, SDL_Renderer* renderer);
		~Hero();
		void setPositionX(int posx);
		void setPositionY(int posy);
		void setLife(int life);
		int getPositionX();
		int getPositionY();
		int getLife();
		bool getOnFloor();
		void setHeroBoxX(int posx);
		void initFrames(SDL_Renderer* renderer);
		void IDLE_moviment(SDL_Renderer* renderer);
		void RUN_moviment(SDL_Renderer* renderer);
		void RUN_AND_GUN_moviment(SDL_Renderer* renderer);
		void SHOOT_UP_moviment(SDL_Renderer* renderer);
		void JUMP_moviment(SDL_Renderer* renderer);
		void DEAD_moviment(SDL_Renderer* renderer);
		void MOVIMENTS_hero(bool* keystates, SDL_Renderer* renderer, SDL_Rect* wall);
		HEROsprites getMoveHero();
		SDL_Rect getHeroBox();
		void setOnTheFloor(bool onTheFloor);

		int getDirection();
	};
}
#endif

