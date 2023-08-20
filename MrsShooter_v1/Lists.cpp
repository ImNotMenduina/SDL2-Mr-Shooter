#include "Lists.h"
#include"collision.h"
#include <iostream>
using namespace std;

// MY LIST OF BULLETS
	//
	//
	//
	// CREATE LLIST
LISTBullets* createList()
{
	LISTBullets* lst = (LISTBullets*)malloc(sizeof(LISTBullets));
	if (lst == NULL) exit(0);
	lst->inicio = NULL;
	lst->size = 0;
	return lst;
}
//
// 
//CREATE AND INSERT BULLET
//
//
void insertBullet(LISTBullets* lst, SDL_Renderer* renderer, int direction, int posx, int posy)
{
	_ONE_BULLET* new_bullet = (_ONE_BULLET*)malloc(sizeof(_ONE_BULLET));
	if (new_bullet == NULL) exit(0);

	Bullet* shoot = new Bullet(posx, posy, direction, renderer);
	if (shoot == NULL) exit(0);

	new_bullet->bullet = shoot;

	if (lst->inicio == NULL)
	{
		new_bullet->proximo = NULL;
		new_bullet->anterior = NULL;
		lst->inicio = new_bullet;
	}
	else
	{
		_ONE_BULLET* aux = lst->inicio;
		_ONE_BULLET* check = NULL;
		while (aux != NULL)
		{
			check = aux;
			aux = aux->proximo;
		}
		new_bullet->proximo = NULL;
		new_bullet->anterior = check;
		check->proximo = new_bullet;
	}
	lst->size++;
}
//
//
//FREE BULLET
//
//
void freeBullet(LISTBullets* lst)
{
	if (lst->inicio == NULL)
		exit(0);

	_ONE_BULLET* aux = lst->inicio;
	_ONE_BULLET* check = NULL;

	while (aux != NULL)
	{
		check = aux;
		aux = aux->proximo;

		if (check->bullet->getLife() < 1)
		{
			if (check == lst->inicio)
			{
				lst->inicio = aux;
				lst->size--;

				//std::cout << "FREELOU BEGIN ###1\n";
			}
			else if (check->proximo == NULL)
			{
				check->anterior->proximo = NULL;
				lst->size--;

				//std::cout << "FREELOU FINAL ###2\n";
			}
			else
			{
				check->anterior->proximo = check->proximo;
				check->proximo->anterior = check->anterior;
				lst->size--;

				//std::cout << "FREELOU MIDDLE ###3\n";
			}
			free(check);
		}
	}
}
//
//
//PRINT BULLET
//
//
void printBullet(LISTBullets* lst, SDL_Renderer* renderer)
{
	_ONE_BULLET* aux = lst->inicio;
	if (aux != NULL)
	{
		while (aux != NULL)
		{
			aux->bullet->SHOOT_bullet(renderer);
			aux = aux->proximo;
		}
	}
}
// MY LIST OF BULLETS
//
//
//



// MY LIST OF ENEMIES
//
//
//
LISTEnemies* createListOfEnemies()
{
	LISTEnemies* lst = (LISTEnemies*)malloc(sizeof(LISTEnemies));
	if (lst == NULL) exit(0);
	lst->inicio = NULL;
	lst->size = 0;
	return lst;
}

void insertEnemies(LISTEnemies* lst, SDL_Renderer* renderer, int posx, int posy)
{
	_ONE_ENEMY* newEnemy = (_ONE_ENEMY*)malloc(sizeof(_ONE_ENEMY));
	if (newEnemy == NULL) exit(0);
	
	Enemy* enemy = new Enemy(posx, posy, renderer);
	if (enemy == NULL) exit(0);

	newEnemy->enemy = enemy;

	if (lst->inicio == NULL)
	{
		newEnemy->proximo = NULL;
		newEnemy->anterior = NULL;
		lst->inicio = newEnemy;
		lst->size++;
	}
	else
	{
		_ONE_ENEMY* aux = lst->inicio;
		_ONE_ENEMY* check = NULL;
		while (aux != NULL)
		{
			check = aux;
			aux = aux->proximo;
		}
		newEnemy->proximo = NULL;
		newEnemy->anterior = check;
		check->proximo = newEnemy;
		lst->size++;
	}
}

void freeEnemies(LISTEnemies* lst)
{
	if (lst == NULL || lst->inicio == NULL) exit(0);

	_ONE_ENEMY* aux = lst->inicio;
	_ONE_ENEMY* check = NULL;

	while (aux != NULL)
	{
		check = aux; 
		aux = aux->proximo;

		if (check->enemy->getLife() < 1)
		{
			if (check == lst->inicio)
			{
				lst->inicio = check->proximo;
				lst->size--;

				std::cout << "FREELOU BEGIN ###1\n";
			}
			else if (check->proximo == NULL)
			{
				check->anterior->proximo = NULL;
				lst->size--;

				std::cout << "FREELOU MIDDLE ###2\n";
			}
			else
			{
				check->anterior->proximo = check->proximo;
				check->proximo->anterior = check->anterior;
				lst->size--;

				std::cout << "FREELOU FINAL ###3\n";
			}
			free(check);
		}
	}
}

void printEnemies(LISTEnemies* lst, LISTBullets* bulletsList, SDL_Renderer* renderer, Hero* hero)
{
	_ONE_ENEMY* aux = lst->inicio;
	if(aux != NULL)
	{
		while (aux != NULL)
		{
			if(aux->enemy->getLife() > 0)
			{
				if(checkCollision(aux->enemy->getActionArea(), hero->getHeroBox()))
				{
					aux->enemy->MOVIMENTS_enemy(hero->getPositionX(), hero->getPositionY());
					aux->enemy->RUN_moviment(renderer);
				}
				else if(checkCollision(aux->enemy->getActionAreaShoot(), hero->getHeroBox()))
				{
					if (hero->getPositionX() > aux->enemy->getPositionX())
					{
						aux->enemy->setDirectionFace(1);
						insertBullet(bulletsList, renderer, aux->enemy->getDirectionFace(), aux->enemy->getPositionX() + (aux->enemy->getEnemyBox().w / 2) + 40, aux->enemy->getPositionY() + (aux->enemy->getEnemyBox().h / 2) - 15);
					}
					else
					{
						aux->enemy->setDirectionFace(-1);
						insertBullet(bulletsList, renderer, aux->enemy->getDirectionFace(), aux->enemy->getPositionX() + (aux->enemy->getEnemyBox().w / 2) - 60, aux->enemy->getPositionY() + (aux->enemy->getEnemyBox().h / 2) - 20);
					}
					aux->enemy->SHOOT_moviment(renderer);
				}
				else
				{
					aux->enemy->IDLE_moviment(renderer);
					aux->enemy->setPositionY(aux->enemy->getPositionY() + ENEMY_GRAVITY);
				}
				aux->enemy->ActionArea(aux->enemy->getEnemyBox());
				//ACTION BOX
				//SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
				//SDL_Rect rect = aux->enemy->getActionArea();
				//SDL_Rect rect2 = aux->enemy->getActionAreaShoot();
				//SDL_RenderDrawRect(renderer, &rect);
				//SDL_RenderDrawRect(renderer, &rect2);
				//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				//
			}
			else
			{
				aux->enemy->DEAD_moviment(renderer);
			}
			aux = aux->proximo;
		}
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
			while (i < tiles.size() &&!checkCollision(aux->enemy->getEnemyBox(), tiles[i].getTileBox()))
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

void freeAll(LISTBullets* lstBullets, LISTEnemies* lstEnemies)
{
	if(lstBullets != NULL)
	{
		if (lstBullets->inicio != NULL)
		{
			_ONE_BULLET* aux = lstBullets->inicio;
			_ONE_BULLET* memDelete = NULL;
			while (aux != NULL)
			{
				memDelete = aux;
				aux = aux->proximo;
				memDelete->bullet->~Bullet();
				//std::cout << "bullet OUT ! \n";
			}
		}
	}
	if(lstEnemies != NULL)
	{
		if (lstEnemies->inicio != NULL)
		{
			_ONE_ENEMY* aux = lstEnemies->inicio;
			_ONE_ENEMY* memDelete = NULL;
			while (aux != NULL)
			{
				memDelete = aux;
				aux = aux->proximo;
				memDelete->enemy->~Enemy();
				//std::cout << "enemy OUT ! \n";
			}
		}
	}
}