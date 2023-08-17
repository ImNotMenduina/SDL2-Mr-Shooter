#include "Enemy.h"
#include <iostream>
using namespace EnemyClass;

	Enemy::Enemy(int posx, int posy, SDL_Renderer* renderer)
	{
		enemyVelocity.speedx = 0;
		enemyVelocity.speedy = 0;
		this->onTheFloor = false;
		this->posx = posx;
		this->posy = posy;
		this->life = 100;
		this->directionFace = 0;
		this->isShooting = false;
		initFrames(renderer);
		ActionArea(this->enemyBox);
	}

	Enemy::~Enemy()
	{
		SDL_DestroyTexture(this->moveEnemy.IDLEenemy);
	}

	void Enemy::setPositionX(int posx)
	{
		this->posx = posx;
	}

	int Enemy::getPositionX()
	{
		return this->posx;
	}

	void Enemy::setPositionY(int posy)
	{
		this->posy = posy;
	}

	int Enemy::getPositionY()
	{
		return this->posy;
	}

	void Enemy::setLife(int life)
	{
		this->life = life;
	}

	int Enemy::getLife()
	{
		return this->life;
	}

	bool Enemy::getIsShooting()
	{
		return this->isShooting;
	}

	void Enemy::setIsShooting(bool shooting)
	{
		this->isShooting = shooting;
	}

	void Enemy::setDirectionFace(int direction)
	{
		this->directionFace = direction;
	}

	int Enemy::getDirectionFace()
	{
		return this->directionFace;
	}

	SDL_Rect Enemy::getEnemyBox()
	{
		return this->enemyBox;
	}

	SDL_Rect Enemy::getActionArea()
	{
		return this->actionArea;
	}

	SDL_Rect Enemy::getActionAreaShoot()
	{
		return this->actionShootArea;
	}

	bool Enemy::getOnTheFloor()
	{
		return this->onTheFloor;
	}

	void Enemy::setOnTheFloor(bool onTheFloor)
	{
		this->onTheFloor = onTheFloor;
	}

	void Enemy::initFrames(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;
		int countFrames = 0;

		this->spriteState[0] = 0; // IDLE
		this->spriteState[1] = 3; // RUN
		this->spriteState[2] = 11; // SHOOT
		this->spriteState[3] = 13; // DIE

		this->moveEnemy.IDLEenemy = loadTexture(renderer, "Assets/Enemy/IDLEenemy.png", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 3; i++)
		{
			enemyBox.x = (TEXTURE_W / 3) * i;
			enemyBox.y = 0;
			enemyBox.w = (TEXTURE_W / 3);
			enemyBox.h = (TEXTURE_H);
			this->moveEnemy.enemyFrames[countFrames] = enemyBox;
			countFrames++;
		}

		this->moveEnemy.RUNenemy = loadTexture(renderer, "Assets/Enemy/RUNenemy.png", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 8; i++)
		{
			enemyBox.x = (TEXTURE_W / 8) * i;
			enemyBox.y = 0;
			enemyBox.w = (TEXTURE_W / 8);
			enemyBox.h = (TEXTURE_H);
			this->moveEnemy.enemyFrames[countFrames] = enemyBox;
			countFrames++;
		}

		this->moveEnemy.SHOOTenemy = loadTexture(renderer, "Assets/Enemy/SHOOTenemy.png", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 2; i++)
		{
			enemyBox.x = (TEXTURE_W / 2) * i;
			enemyBox.y = 0;
			enemyBox.w = (TEXTURE_W / 2);
			enemyBox.h = (TEXTURE_H);
			this->moveEnemy.enemyFrames[countFrames] = enemyBox;
			countFrames++;
		}

		this->moveEnemy.DEADhero = loadTexture(renderer, "Assets/Enemy/DEADenemy.png", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 4; i++)
		{
			enemyBox.x = (TEXTURE_W / 4) * i;
			enemyBox.y = 0;
			enemyBox.w = (TEXTURE_W / 4);
			enemyBox.h = (TEXTURE_H);
			this->moveEnemy.enemyFrames[countFrames] = enemyBox;
			countFrames++;
		}


	}

	void Enemy::IDLE_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;

		SDL_QueryTexture(this->moveEnemy.IDLEenemy, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		enemyBox.x = this->posx;
		enemyBox.y = this->posy;
		enemyBox.w = (TEXTURE_W / 3) * 2;
		enemyBox.h = (TEXTURE_H) * 2;
		SDL_RenderCopy(renderer, this->moveEnemy.IDLEenemy, &this->moveEnemy.enemyFrames[this->spriteState[0]], &enemyBox);

		this->spriteState[0]++;

		if (this->spriteState[0] > 2)
		{
			this->spriteState[0] = 0;
		}
	}

	void Enemy::RUN_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;

		SDL_QueryTexture(this->moveEnemy.RUNenemy, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		enemyBox.x = this->posx;
		enemyBox.y = this->posy;
		enemyBox.w = (TEXTURE_W / 8) * 2;
		enemyBox.h = (TEXTURE_H) * 2;

		if(this->directionFace == 1)
		{
		SDL_RenderCopyEx(renderer, this->moveEnemy.RUNenemy, &this->moveEnemy.enemyFrames[this->spriteState[1]], &enemyBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
		else if(this->directionFace == 2)
		{
			SDL_RenderCopy(renderer, this->moveEnemy.RUNenemy, &this->moveEnemy.enemyFrames[this->spriteState[1]], &enemyBox);
		}

		this->spriteState[1]++;

		if (this->spriteState[1] > 8)
		{
			this->spriteState[1] = 3;
		}
	}

	void Enemy::SHOOT_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;

		SDL_QueryTexture(this->moveEnemy.SHOOTenemy, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		enemyBox.x = this->posx;
		enemyBox.y = this->posy;
		enemyBox.w = (TEXTURE_W / 2) * 2;
		enemyBox.h = (TEXTURE_H) * 2;
		if(this->directionFace == 1)
		{
			SDL_RenderCopy(renderer, this->moveEnemy.SHOOTenemy, &this->moveEnemy.enemyFrames[this->spriteState[2]], &enemyBox);
		}
		else if(this->directionFace == -1)
		{
			SDL_RenderCopyEx(renderer, this->moveEnemy.SHOOTenemy, &this->moveEnemy.enemyFrames[this->spriteState[2]], &enemyBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}

		this->spriteState[2]++;

		if (this->spriteState[2] > 12)
		{
			this->spriteState[2] = 11;
		}
	}

	void Enemy::DEAD_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;

		SDL_QueryTexture(this->moveEnemy.DEADhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		enemyBox.x = this->posx;
		enemyBox.y = this->posy;
		enemyBox.w = (TEXTURE_W / 4) * 2;
		enemyBox.h = (TEXTURE_H) * 2;
		SDL_RenderCopy(renderer, this->moveEnemy.DEADhero, &this->moveEnemy.enemyFrames[this->spriteState[3]], &enemyBox);

		this->spriteState[3]++;

		if (this->spriteState[3] > 16)
		{
			this->spriteState[3] = 16;
		}
	}
	
	void Enemy::ActionArea(SDL_Rect currentBox)
	{
		this->actionArea.w = currentBox.w * 3;
		this->actionArea.h = currentBox.h;
		this->actionArea.x = this->posx - (actionArea.w / 2) + (currentBox.w / 2);
		this->actionArea.y = this->posy;

		this->actionShootArea.w = currentBox.w * 6;
		this->actionShootArea.h = currentBox.h;
		this->actionShootArea.x = this->posx - (actionShootArea.w / 2) + (currentBox.w / 2); 
		this->actionShootArea.y = this->posy;
	}
	


	void Enemy::MOVIMENTS_enemy(int heroPosx, int heroPosy)
	{
			// x axis
			if (heroPosx < this->posx)
			{
				this->enemyVelocity.speedx = ENEMY_SPEED;
				this->enemyVelocity.speedy = ENEMY_GRAVITY;
				
				this->posx -= enemyVelocity.speedx;
				this->posy += this->enemyVelocity.speedy;
				this->directionFace = 1;	
			}
			if (heroPosx > this->posx)
			{
				this->enemyVelocity.speedx = ENEMY_SPEED;
				this->enemyVelocity.speedy = ENEMY_GRAVITY;

				this->posx += enemyVelocity.speedx;
				this->posy += this->enemyVelocity.speedy;

				this->directionFace = 2;
			}
	}
	

