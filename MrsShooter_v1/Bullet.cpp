#include "Bullet.h"
using namespace BulletClass;

	//**bulletBox 
	Bullet::Bullet(int posx, int posy, int direction, SDL_Renderer* renderer)
	{
		this->posx = posx;
		this->posy = posy;
		this->life = 1;
		this->direction = direction;
		this->BULLET = IMG_LoadTexture(renderer, "Assets/Enemy/SHOOT.png");
	}

	void Bullet::SHOOT_bullet(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;

		SDL_QueryTexture(this->BULLET, NULL, NULL, &TEXTURE_W, &TEXTURE_H);
	
		bulletBox.x = this->posx;
		bulletBox.y = this->posy;
		bulletBox.w = TEXTURE_W * 3;
		bulletBox.h = TEXTURE_H * 3;

		if (this->posx > 0 && this->posx < SCREEN_WIDTH)
		{
			SDL_RenderCopy(renderer, this->BULLET, NULL, &bulletBox);
		}
		else
		{
			this->setLife(0);
		}

		if (this->direction == 1)
			this->posx += 10;
		else if(this->direction == -1)
			this->posx -= 10;
	}
	Bullet::~Bullet() {
		SDL_DestroyTexture(this->BULLET);
	}

	void Bullet::setPositionX(int posx)
	{
		this->posx = posx;
	}

	int Bullet::getPositionX()
	{
		return this->posx;
	}

	void Bullet::setPositionY(int posy)
	{
		this->posy = posy;
	}

	int Bullet::getPositionY()
	{
		return this->posy;
	}

	void Bullet::setLife(int life)
	{
		this->life = life;
	}

	int Bullet::getLife()
	{
		return this->life;	
	}

	SDL_Rect Bullet::getBulletBox()
	{
		return this->bulletBox;
	}

	int Bullet::getDirection()
	{
		return this->direction;
	}