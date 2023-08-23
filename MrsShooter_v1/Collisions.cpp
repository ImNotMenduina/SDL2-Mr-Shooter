#include "collision.h"

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y; 
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	
	if (rightA <= leftB)
		return false;
	if (rightB <= leftA)
		return false;
	if (bottomA <= topB)
		return false;
	if (bottomB <= topA)
		return false;

	return true;
}

void collisionBulletAgainstEnemy(LISTBullets* listBullets, LISTEnemies* listEnemies)
{
	_ONE_BULLET* aux = listBullets->inicio;

	while (aux != NULL)
	{	
		_ONE_ENEMY* aux2 = listEnemies->inicio;
		while (aux2 != NULL)
		{
			if ((aux2->enemy->getLife() > 0) && checkCollision(aux->bullet->getBulletBox(), aux2->enemy->getEnemyBox()))
			{
				aux2->enemy->setLife(aux2->enemy->getLife() - 10);
				aux->bullet->setLife(0);
			}
			aux2 = aux2->proximo;
		}
		aux = aux->proximo;
	}
}

void collisionHeroAgainstEnemy(Hero* hero, LISTEnemies* list)
{
	_ONE_ENEMY* aux = list->inicio;
	while (aux != NULL)
	{
		if ((aux->enemy->getLife() > 0) && checkCollision(hero->getHeroBox(), aux->enemy->getEnemyBox()))
		{
			hero->setLife(hero->getLife() - 5); 
		}
		aux = aux->proximo;
	}
}

void collisionEnemyTile(LISTEnemies* lst, std::vector<Tile>& tiles)
{
	_ONE_ENEMY* aux = lst->inicio;
	bool collision = false;
	int i = 0;
	if (aux != NULL)
	{
		while (aux != NULL)
		{
			collision = false;
			while (i < tiles.size() && !checkCollision(aux->enemy->getEnemyBox(), tiles[i].getTileBox()))
			{
				i++;
			}

			if (i < tiles.size())
			{
				collision = true;
			}

			if (collision)
			{
				aux->enemy->setPositionY(tiles[i].getPosY() - aux->enemy->getEnemyBox().h); //***
				aux->enemy->setOnTheFloor(true);
			}
			else
			{
				aux->enemy->setOnTheFloor(false);
			}

			i = 0;
			aux = aux->proximo;
		}
	}
}

void collisionHeroTile(std::vector<Tile>& tiles, Hero* hero, SDL_Renderer* renderer)
{
	int i = 0;
	bool collision = false;
	SDL_Rect base;
	base.x = hero->getHeroBox().x;
	base.y = hero->getHeroBox().y;
	base.w = hero->getHeroBox().w;
	base.h = hero->getHeroBox().h;

	while (i < tiles.size() && !checkCollision(tiles[i].getTileBox(), base))
	{
		i++;
	}

	if (i < tiles.size())
		collision = true;

	if (collision)
	{
		hero->setPositionY(tiles[i].getPosY() - hero->getHeroBox().h + 3);
		hero->setOnTheFloor(true);
	}
	else
	{
		hero->setOnTheFloor(false);
	}

	////
	///// HERO TILE COLLIDER
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &base);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	/////
	////
}

//
//
//************** IMPORTANTE ***************
// ERRO DO TIPO, C2065, Não sei oq houve, ainda.
//
//

//bool checkCollisionCIRCLE_RECT(SDL_Rect a, CIRCLE b)
//{
//
//	return true;
//}

