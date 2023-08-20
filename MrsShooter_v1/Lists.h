#ifndef List_H
#define List_H

#include<vector>
#include "Bullet.h"
#include "Enemy.h"
#include "Hero.h"

using namespace BulletClass;
using namespace EnemyClass;
using namespace HeroClass;
using namespace std;

// LIST OF BULLETS
//
//
	struct bulletNode
	{
		Bullet* bullet;
		struct bulletNode* proximo;
		struct bulletNode* anterior;
	};
	typedef struct bulletNode _ONE_BULLET;

	struct listBullets
	{
		int size;
		_ONE_BULLET* inicio;
	};

	typedef struct listBullets LISTBullets;


	// LIST OF ENEMIES
	//
	//
	struct enemyNode
	{
		Enemy* enemy;
		struct enemyNode* proximo;
		struct enemyNode* anterior;
	};
	typedef struct enemyNode _ONE_ENEMY;

	struct listEnemies
	{
		int size;
		_ONE_ENEMY* inicio;
	};

	typedef struct listEnemies LISTEnemies;


//// LIST OF BULLETS
//
//
LISTBullets* createList();
void insertBullet(LISTBullets* lst, SDL_Renderer* renderer, int direction, int posx, int posy);
void printBullet(LISTBullets* lst, SDL_Renderer* renderer);
void freeBullet(LISTBullets* lst);
// LIST OF ENEMIES
//
//
LISTEnemies* createListOfEnemies();
void freeEnemies(LISTEnemies* lst);
void insertEnemies(LISTEnemies* lst, SDL_Renderer* renderer, int posx, int posy);
void printEnemies(LISTEnemies* lst, LISTBullets* bulletsList, SDL_Renderer* renderer, Hero* hero);

void freeAll(LISTBullets* lstBullets, LISTEnemies* lstEnemies);
//int distance(int x1, int y1, int x2, int y2);

#endif