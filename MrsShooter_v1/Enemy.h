#ifndef Enemy_H
#define Enemy_H
#define ENEMY_SPEED 2
#define ENEMY_GRAVITY 3

#include<SDL_image.h>
#include "texture.h"
#include "Timer.h"
#include "structus.h"

using namespace TimerClass;

namespace EnemyClass
{
	class Enemy {
	private:
		//posx and posy
		int posx;
		int posy;
		SPEED enemyVelocity;

		//game stats
		bool isChasing;
		int life;

		//sprites logics
		int relaxMoviments;
		int directionFace;
		int spriteState[4];
		bool isShooting;
		bool onTheFloor;
		ENEMYsprites moveEnemy;

		//enemy hit boxes
		SDL_Rect enemyBox;
		SDL_Rect actionArea;
		SDL_Rect actionShootArea;

		//enemy timers
		Timer walkingTimer;
	public:
		Enemy(int posx, int posy, SDL_Renderer* renderer);
		~Enemy();

		//coord functions
		void setPositionX(int posx);
		void setPositionY(int posy);
		int getPositionX();
		int getPositionY();

		//life
		void setLife(int life);
		int getLife();

		//sprite direction
		void setDirectionFace(int direction);
		int getDirectionFace();

		//enemy hit boxes
		void setIsChasing(bool isChasing);
		SDL_Rect getEnemyBox();
		SDL_Rect getActionArea();
		SDL_Rect getActionAreaShoot();

		//enemy init sprites
		void initFrames(SDL_Renderer* renderer);

		//enemy print on screen
		void IDLE_moviment(SDL_Renderer* renderer);
		void RUN_moviment(SDL_Renderer* renderer);
		void SHOOT_moviment(SDL_Renderer* renderer);
		void DEAD_moviment(SDL_Renderer* renderer);
		void MOVIMENTS_enemy(int heroPosx, int heroPosy, SDL_Renderer* renderer);
		void ActionArea(SDL_Rect actionArea);

		//enemy is on the floor
		bool getOnTheFloor();
		void setOnTheFloor(bool onTheFloor);
	};
}

#endif