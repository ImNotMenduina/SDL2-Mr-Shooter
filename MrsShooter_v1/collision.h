#ifndef collision_H
#define collision_H
#include <malloc.h>
#include "structus.h"
#include "Lists.h"

using namespace HeroClass;

bool checkCollision(SDL_Rect a, SDL_Rect b);
//bool checkCollisionCIRCLE_RECT(SDL_Rect a, CIRCLE b);
void collisionBulletAgainstEnemy(LISTBullets* listBullets, LISTEnemies* listEnemies);
void collisionHeroAgainstEnemy(Hero* hero, LISTEnemies* list);

#endif 