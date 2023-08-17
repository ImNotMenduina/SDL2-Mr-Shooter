#ifndef Bullet_H
#define Bullet_H

#include "structus.h"
#include <SDL_image.h>
#include "Screen.h"

namespace BulletClass
{
	class Bullet
	{
	private:
		int posx;
		int posy;
		int life;
		int direction;
		SDL_Texture* BULLET;
		SDL_Rect bulletBox;
	public:
		Bullet(int posx, int posy, int direction, SDL_Renderer* renderer);
		~Bullet();
		void SHOOT_bullet(SDL_Renderer* renderer);
		void setPositionX(int posx);
		void setPositionY(int posy);
		int getPositionX();
		int getPositionY();
		void setLife(int life);
		int getDirection();
		int getLife();
		SDL_Rect getBulletBox();
	};
}
#endif
