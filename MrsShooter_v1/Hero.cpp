#include "Hero.h"
#include<iostream>
#define GRAVITY 3
using namespace HeroClass;

	Hero::Hero(int posx, int posy, SDL_Renderer* renderer)
	{
		this->heroVelocity.speedx = 0;
		this->heroVelocity.speedy = 0;
		this->direction = 1;
		this->life = 100;
		this->posx = posx;
		this->posy = posy;
		this->onTheFloor = false;
		initFrames(renderer);
	}

	Hero::~Hero() {
		SDL_DestroyTexture(this->moveHero.IDLEhero);
		SDL_DestroyTexture(this->moveHero.RUNhero);
		SDL_DestroyTexture(this->moveHero.FIREhero);
		SDL_DestroyTexture(this->moveHero.FIREUPhero);
		SDL_DestroyTexture(this->moveHero.JUMPhero);
		SDL_DestroyTexture(this->moveHero.DEADhero);
	}

	void Hero::setPositionX(int posx)
	{
		this->posx = posx;
	}

	int Hero::getPositionX()
	{
		return this->posx;
	}

	void Hero::setPositionY(int posy)
	{
		this->posy = posy;
	}

	int Hero::getPositionY()
	{
		return this->posy;
	}

	void Hero::setLife(int life)
	{
		this->life = life;
	}

	int Hero::getLife()
	{
		return this->life;
	}

	HEROsprites Hero::getMoveHero()
	{
		return this->moveHero;
	}

	SDL_Rect Hero::getHeroBox()
	{
		return this->heroBox;
	}

	void Hero::setHeroBoxX(int posx)
	{
		this->heroBox.x = posx;
	}

	bool Hero::getOnFloor()
	{
		return this->onTheFloor;
	}

	int Hero::getDirection()
	{
		return this->direction;
	}

	void Hero::initFrames(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;
		int spriteCounter = 0;
		//IDLE == THIS->SPRITESTATE[0]
		//IDLE INDEX 0, 1, 2, 3 , 4, 5
		this->moveHero.IDLEhero = loadTexture(renderer, "Assets/Hero/IDLEhero.png", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 6; i++)
		{
			//SDL_Rect rect;
			heroBox.x = (TEXTURE_W / 6) * i;
			heroBox.y = 0;
			heroBox.w = TEXTURE_W / 6;
			heroBox.h = TEXTURE_H;
			this->moveHero.heroFrames[spriteCounter] = heroBox;
			////std::cout << "IDLE : " << spriteCounter << "\n";
			spriteCounter++;	
		}
		//RUN == THIS->SPRITESTATE[1]
		//RUN INDEXES 6,7,8,9,10,11,12,13
		this->moveHero.RUNhero = loadTexture(renderer, "Assets/Hero/RUNhero.png", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 8; i++)
		{
			heroBox.x = (TEXTURE_W / 8) * i;
			heroBox.y = 0;
			heroBox.w = TEXTURE_W / 8;
			heroBox.h = TEXTURE_H;
			this->moveHero.heroFrames[spriteCounter] = heroBox;
			////std::cout << "RUN : " << spriteCounter << "\n";
			spriteCounter++;
		}
		//FIRE == THIS->SPRITESTATE[2]
		//FIRE INDEXES 14,15,16,17,18,19,20,21
		this->moveHero.FIREhero = loadTexture(renderer, "Assets/Hero/FIREhero.png", & TEXTURE_W, & TEXTURE_H);

		for (int i = 0; i < 8; i++)
		{
			heroBox.x = (TEXTURE_W / 8) * i;
			heroBox.y = 0;
			heroBox.w = TEXTURE_W / 8;
			heroBox.h = TEXTURE_H;
			this->moveHero.heroFrames[spriteCounter] = heroBox;
			////std::cout << "FIRE&RUN : " << spriteCounter << "\n";
			spriteCounter++;
		}
		//FIRE UP == THIS->SPRITESTATE[3]
		//FIRE UP INDEXES 22,23
		this->moveHero.FIREUPhero = loadTexture(renderer, "Assets/Hero/FIREUPhero.png", &TEXTURE_W, & TEXTURE_H);

		for (int i = 0; i < 2; i++)
		{
			heroBox.x = (TEXTURE_W / 2) * i;
			heroBox.y = 0;
			heroBox.w = TEXTURE_W / 2;
			heroBox.h = TEXTURE_H;
			this->moveHero.heroFrames[spriteCounter] = heroBox;
			////std::cout << "FIRE&UP : " << spriteCounter << "\n";
			spriteCounter++;
		}
		//JUMP == THIS->SPRITESTATE[4]
		//JUMP INDEX 24
		this->moveHero.JUMPhero = loadTexture(renderer, "Assets/Hero/JUMPhero.png", &TEXTURE_W, &TEXTURE_H);

		heroBox.x = 0;
		heroBox.y = 0;
		heroBox.w = (TEXTURE_W);
		heroBox.h = (TEXTURE_H);
		this->moveHero.heroFrames[spriteCounter] = heroBox;
		////std::cout << "JUMP : " << spriteCounter << "\n";
		spriteCounter++;

		//DEAD == THIS->SPRITESTATE[5]
		//DEAD INDEX 25
		this->moveHero.DEADhero = loadTexture(renderer, "Assets/Hero/DEADhero.PNG", &TEXTURE_W, &TEXTURE_H);

		for (int i = 0; i < 5; i++)
		{
			heroBox.x = (TEXTURE_W / 5) * i;
			heroBox.y = 0;
			heroBox.w = (TEXTURE_W / 5);
			heroBox.h = (TEXTURE_H);
			this->moveHero.heroFrames[spriteCounter] = heroBox;
			////std::cout << "DEAD : " << spriteCounter << "\n";
			spriteCounter++;
		}
	}

	void Hero::IDLE_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;
		int static IDLE_MOVIMENT = 0;

		SDL_QueryTexture(this->moveHero.IDLEhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		heroBox.x = this->getPositionX();
		heroBox.y = this->getPositionY();
		heroBox.w = (TEXTURE_W / 6) * 2;
		heroBox.h = TEXTURE_H * 2;

		if(this->direction == 1)
		{
			SDL_RenderCopy(renderer, this->moveHero.IDLEhero, &this->moveHero.heroFrames[IDLE_MOVIMENT], &heroBox);
		}
		else if(this->direction == -1)
		{
			SDL_RenderCopyEx(renderer, this->moveHero.IDLEhero, &this->moveHero.heroFrames[IDLE_MOVIMENT], &heroBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}

		IDLE_MOVIMENT++;

		if (IDLE_MOVIMENT > 5)
		{
			IDLE_MOVIMENT = 0;
		}
	}

	void Hero::RUN_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;
		int static RUN_MOVIMENT = 6;

		SDL_QueryTexture(this->moveHero.RUNhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		heroBox.x = this->getPositionX();
		heroBox.y = this->getPositionY();
		heroBox.w = (TEXTURE_W / 8) * 2;
		heroBox.h = TEXTURE_H * 2;

		if(this->direction == 1)
		{
			SDL_RenderCopy(renderer, this->moveHero.RUNhero, &this->moveHero.heroFrames[RUN_MOVIMENT], &heroBox);
		}
		else if(this->direction == -1)
		{
			SDL_RenderCopyEx(renderer, this->moveHero.RUNhero, &this->moveHero.heroFrames[RUN_MOVIMENT], &heroBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}

		RUN_MOVIMENT++;

		if (RUN_MOVIMENT > 13)
		{
			RUN_MOVIMENT = 6;
		}
	}
	
	void Hero::RUN_AND_GUN_moviment(SDL_Renderer* renderer)
	{
		int static RUN_AND_GUN_MOVIMENT = 14;
		int TEXTURE_W, TEXTURE_H;

		SDL_QueryTexture(this->moveHero.FIREhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		heroBox.x = this->getPositionX();
		heroBox.y = this->getPositionY();
		heroBox.w = (TEXTURE_W / 8) * 2;
		heroBox.h = TEXTURE_H * 2;

		if(this->direction == 1)
		{
			SDL_RenderCopy(renderer, this->moveHero.FIREhero, &this->moveHero.heroFrames[RUN_AND_GUN_MOVIMENT], &heroBox);
		}
		else if(this->direction == -1)
		{
			SDL_RenderCopyEx(renderer, this->moveHero.FIREhero, &this->moveHero.heroFrames[RUN_AND_GUN_MOVIMENT], &heroBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}

		RUN_AND_GUN_MOVIMENT++;

		if (RUN_AND_GUN_MOVIMENT > 21)
		{
			RUN_AND_GUN_MOVIMENT = 14;
		}
	}

	void Hero::SHOOT_UP_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;
		int static SHOOT_UP_MOVIMENT = 22;

		SDL_QueryTexture(this->moveHero.FIREUPhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		heroBox.x = this->getPositionX();
		heroBox.y = this->getPositionY();
		heroBox.w = (TEXTURE_W / 2) * 2;
		heroBox.h = TEXTURE_H * 2;

		if(this->direction == 1)
		{
			SDL_RenderCopy(renderer, this->moveHero.FIREUPhero, &this->moveHero.heroFrames[SHOOT_UP_MOVIMENT], &heroBox);
		}
		else if(this->direction == -1)
		{
			SDL_RenderCopyEx(renderer, this->moveHero.FIREUPhero, &this->moveHero.heroFrames[SHOOT_UP_MOVIMENT], &heroBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
		SHOOT_UP_MOVIMENT++;

		if (SHOOT_UP_MOVIMENT > 23)
		{
			SHOOT_UP_MOVIMENT = 22;
		}		
	}

	void Hero::JUMP_moviment(SDL_Renderer* renderer)
	{
		int TEXTURE_W, TEXTURE_H;
		int INDEX_JUMP = 24;

		SDL_QueryTexture(this->moveHero.JUMPhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		heroBox.x = this->posx;
		heroBox.y = this->posy;
		heroBox.w = TEXTURE_W * 2;
		heroBox.h = TEXTURE_H * 2;
		if(this->direction == 1)
		{
			SDL_RenderCopy(renderer, this->moveHero.JUMPhero, &this->moveHero.heroFrames[INDEX_JUMP], &heroBox);
		}
		else if(this->direction == -1)
		{
			SDL_RenderCopyEx(renderer, this->moveHero.JUMPhero, &this->moveHero.heroFrames[INDEX_JUMP], &heroBox, NULL, NULL, SDL_FLIP_HORIZONTAL);
		}
	}

	void Hero::DEAD_moviment(SDL_Renderer* renderer)
	{
		//static, do not instancea a new deadFrame every call
		int TEXTURE_W, TEXTURE_H;
		int static deadFrame = 0;

		SDL_QueryTexture(this->moveHero.DEADhero, NULL, NULL, &TEXTURE_W, &TEXTURE_H);

		heroBox.x = this->posx;
		heroBox.y = this->posy;
		heroBox.w = (TEXTURE_W / 5) * 2;
		heroBox.h = (TEXTURE_H) * 2;
		
		if(this->direction == 1)
		{
			SDL_RenderCopy(renderer, this->moveHero.DEADhero, &this->moveHero.heroFrames[24 + deadFrame], &heroBox);
		}
		else if(this->direction == -1)
		{
			SDL_RenderCopy(renderer, this->moveHero.DEADhero, &this->moveHero.heroFrames[24 + deadFrame], &heroBox);
		}
		deadFrame++;

		if (deadFrame > 4)
		{
			deadFrame = 4;
		}
	}

	void Hero::setOnTheFloor(bool onTheFloor)
	{
		this->onTheFloor = onTheFloor;
	}

	void Hero::MOVIMENTS_hero(bool* keystates, SDL_Renderer* renderer, SDL_Rect* wall)
	{
		if(this->life > 0)
		{
			//this->heroVelocity.speedy -= GRAVITY;

			if (keystates[3] && keystates[4] && this->onTheFloor)
			{
				this->posx += 1 * HERO_RUN_AND_GUN;
				this->RUN_AND_GUN_moviment(renderer);
			}
			else if (keystates[5] && keystates[2] && this->onTheFloor)
			{
				this->onTheFloor = false;
				this->direction = -1;
				this->heroVelocity.speedx = 10;
				this->heroVelocity.speedy = 20;
				this->posx -= this->heroVelocity.speedx;
				this->posy -= this->heroVelocity.speedy;
				this->heroVelocity.speedy -= GRAVITY;
				if (this->posx < 0)
				{
					this->posx += this->heroVelocity.speedx;
				}
				this->JUMP_moviment(renderer);
			}
			else if (keystates[5] && keystates[3] && this->onTheFloor)
			{
				this->onTheFloor = false;
				this->direction = 1;
				this->heroVelocity.speedx = 10;
				this->heroVelocity.speedy = 20;
				this->posx += this->heroVelocity.speedx;
				this->posy -= this->heroVelocity.speedy;
				this->heroVelocity.speedy -= GRAVITY;
				if (this->posx > wall->w)
				{
					this->posx -= this->heroVelocity.speedx;
				}
				this->JUMP_moviment(renderer);
			}
			else if (keystates[0] && this->onTheFloor)
			{
				//W
				this->posy -= 1 * HERO_RUN_AND_GUN;
				if (this->posy < 0)
				{
					this->posy += HERO_RUN_AND_GUN;
				}
				this->RUN_moviment(renderer);
			}
			else if (keystates[1])
			{
				//S
				this->heroVelocity.speedx = 10;
				this->posy += 1 * this->heroVelocity.speedx;
				if (this->heroBox.y + this->heroBox.h > wall->h)
				{
					this->posy -= this->heroVelocity.speedx;
				}
				this->RUN_moviment(renderer);
			}
			else if (keystates[2])
			{
				//A
				this->direction = -1;
				this->heroVelocity.speedx = 10;
				this->posx -= this->heroVelocity.speedx;
				if (this->posx < 0)
				{
					this->posx += this->heroVelocity.speedx;
					this->heroBox.x = this->posx;
				}
				if(this->onTheFloor)
				{
					this->RUN_moviment(renderer);
				}
				else
				{
					this->JUMP_moviment(renderer);
					this->posy -= this->heroVelocity.speedy;
					this->heroVelocity.speedy -= GRAVITY;
				}
			}
			//A + SPACE
			else if (keystates[3])
			{
				//D
				this->direction = 1;
				this->heroVelocity.speedx = 10;
				this->posx += this->heroVelocity.speedx;
				if (this->posx + this->heroBox.w > wall->w)
				{
					this->posx -= HERO_RUN_AND_GUN;
				}

				if (this->onTheFloor)
				{
					this->RUN_moviment(renderer);
				}
				else
				{
					this->JUMP_moviment(renderer);
					this->posy -= this->heroVelocity.speedy;
					this->heroVelocity.speedy -= GRAVITY;
				}
			}
			else if (keystates[4] && this->onTheFloor)
			{
				
				this->SHOOT_UP_moviment(renderer);
			}
			else if (keystates[5] && this->onTheFloor)
			{
				this->onTheFloor = false;
				this->heroVelocity.speedy = 15;
				this->posy -= this->heroVelocity.speedy;
				this->JUMP_moviment(renderer);
			}
			else if (!this->onTheFloor)
			{
				this->posy -= this->heroVelocity.speedy;
				this->heroVelocity.speedy -= GRAVITY;
				this->JUMP_moviment(renderer);
			}
			else
			{
				this->IDLE_moviment(renderer);
			}
		}
		else
		{
			this->DEAD_moviment(renderer);
		}
	}
