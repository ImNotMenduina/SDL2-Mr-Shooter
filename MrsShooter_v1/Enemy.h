#ifndef Enemy_H
#define Enemy_H
#define ENEMY_SPEED 2
#define ENEMY_GRAVITY 3
#include "structus.h"
#include "Hero.h"
#include<SDL_image.h>
#include <fstream>

namespace EnemyClass
{
	class Enemy {
	private:
		int posx;
		int posy;
		int life;
		int directionFace;
		int spriteState[4];
		bool isShooting;
		bool onTheFloor;
		ENEMYsprites moveEnemy;
		SDL_Rect enemyBox;
		SDL_Rect actionArea;
		SDL_Rect actionShootArea;
		SPEED enemyVelocity;
		//CIRCLE enemyRadius;
	public:
		Enemy(int posx, int posy, SDL_Renderer* renderer);
		~Enemy();
		void setPositionX(int posx);
		void setPositionY(int posy);
		void setLife(int life);
		void setDirectionFace(int direction);
		int getDirectionFace();
		int getPositionX();
		int getPositionY();
		int getLife();
		bool getIsShooting();
		void setIsShooting(bool shooting);
		SDL_Rect getEnemyBox();
		SDL_Rect getActionArea();
		SDL_Rect getActionAreaShoot();
		void initFrames(SDL_Renderer* renderer);
		void IDLE_moviment(SDL_Renderer* renderer);
		void RUN_moviment(SDL_Renderer* renderer);
		void SHOOT_moviment(SDL_Renderer* renderer);
		void DEAD_moviment(SDL_Renderer* renderer);
		void MOVIMENTS_enemy(int heroPosx, int heroPosy);
		void ActionArea(SDL_Rect actionArea);

		bool getOnTheFloor();
		void setOnTheFloor(bool onTheFloor);
	};
}

#endif