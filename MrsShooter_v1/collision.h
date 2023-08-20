#ifndef collision_H
#define collision_H
#include <malloc.h>
#include <vector>

#include "structus.h"
#include "Lists.h"
#include "Tile.h"

using namespace TileClass;
using namespace HeroClass;

bool checkCollision(SDL_Rect a, SDL_Rect b);
void collisionBulletAgainstEnemy(LISTBullets* listBullets, LISTEnemies* listEnemies);
void collisionHeroAgainstEnemy(Hero* hero, LISTEnemies* list);
void collisionEnemyTile(LISTEnemies* lst, std::vector<Tile>& tiles);

#endif 