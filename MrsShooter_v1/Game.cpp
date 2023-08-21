#include "Game.h"

int main(int argv, char* argc[])
{
	//SDL WINDOW
	SDL_Window* window = nullptr; 
	//init.SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "error: SDL_Init()";
	}

	window = SDL_CreateWindow("Mrs_Shooter",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);
	
	if (window == nullptr)
	{
		std::cout << "error: SDL_CreateWindow()"; 
	}

	IMG_Init(IMG_INIT_PNG);

	//SDL RENDERER
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		std::cout << "error: SDL_CreateRenderer()";
	}

	auto map = new int[40][30];

	auto tile = new SDL_Rect[40][30];

	SDL_Rect rect;
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 30; y++)
		{
			rect.x = x * 16;
			rect.y = y * 16;
			rect.w = 16 ;
			rect.h = 16 ;
			tile[x][y] = rect;
		}
	}

	std::vector<Tile> chao;

	for (int x = 0; x < 40; x++)
	{
		
		for (int y = 0; y < 30; y++)
		{
			//int stackHeight = heights[x];
			//if (y > stackHeight)
			//{
			//	map[x][y] = 1;
			//}
			if(y == 25) //|| y == stackHeight)
			{
				map[x][y] = 0;
				chao.push_back(Tile(x * 16, y * 16, renderer));			
			}
			if(y == 10 && x > 20 ||
				y == 12 && x == 14 ||
				 y==20 && x > 20 ||
					y == 15 && x < 10 ||
					y == 18 && x == 12)
			{
				map[x][y] = 0;
				chao.push_back(Tile(x * 16, y * 16, renderer));
			}
		}
	}

	SDL_Rect wallCollider; 
	wallCollider.x = 0;
	wallCollider.y = 0;
	wallCollider.w = SCREEN_WIDTH;
	wallCollider.h = SCREEN_HEIGHT;

	Hero* hero = new Hero(200, 200, renderer);

	LISTBullets* lstBullets = createList();
	LISTEnemies* lstEnemies = createListOfEnemies();

	insertEnemies(lstEnemies, renderer, 400, 200);
	insertEnemies(lstEnemies, renderer, 500, 200);

	bool isRunning = true;
	bool keystates[6] = { false };

	SDL_Texture* background3 = loadTexture(renderer, "maps/nuvens_3.png", NULL, NULL);
	SDL_Texture* background2 = loadTexture(renderer, "maps/nuvens_2.png", NULL, NULL);
	SDL_Texture* background1 = loadTexture(renderer, "maps/nuvens_1.png", NULL, NULL);
	SDL_Texture* background = loadTexture(renderer, "maps/mapback.png", NULL, NULL);
	SDL_Texture* mato = loadTexture(renderer, "maps/mato.png", NULL, NULL);

	Timer time = Timer();
	time.Start();
	std::cout << "timer was started at: " << time.getTicks();

	while(isRunning)
	{
		//DEFAULT (IDLE)
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, background3, NULL, NULL);
		SDL_RenderCopy(renderer, background2, NULL, NULL);
		SDL_RenderCopy(renderer, background1, NULL, NULL);
		SDL_RenderCopy(renderer, background, NULL, NULL);

		
		if (hero->getLife() > 0 && lstEnemies->size < 3)
		{
			insertEnemies(lstEnemies, renderer, rand() % 600 + 1, rand() % 400 + 1);
			insertEnemies(lstEnemies, renderer, rand() % 600 + 1, rand() % 400 + 1);
			std::cout << lstEnemies->size;
		}

		SDL_Event events;

		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT)
			{
				std::cout << "timer was FINISHED at: " << time.getTicks();
				time.Stop();
				isRunning = false;
			}

			if (events.type == SDL_KEYDOWN)
			{
				if (events.key.keysym.sym == SDLK_w)
				{
					//std::cout << "w";
					//keystates[0] = true;
				}
				if (events.key.keysym.sym == SDLK_s)
				{
					//std::cout << "s";
					//keystates[1] = true;
				}
				if (events.key.keysym.sym == SDLK_a)
				{
					//std::cout << "a";
					keystates[2] = true;
				}
				if (events.key.keysym.sym == SDLK_d)
				{
					//std::cout << "d";
					keystates[3] = true;
				}
				if (events.key.keysym.sym == SDLK_f)
				{
					//std::cout << "f";
					keystates[4] = true;
					if(hero->getDirection() == 1)
						insertBullet(lstBullets, renderer, hero->getDirection(), hero->getPositionX() + 30 * 2, hero->getPositionY() + 8 * 2);
					else
						insertBullet(lstBullets, renderer, hero->getDirection(), hero->getPositionX(), hero->getPositionY() + 8 * 2);
				}
				if (events.key.keysym.sym == SDLK_SPACE)
				{
					//std::cout << "SPACE";
					keystates[5] = true;
				}
				
			}
			if (events.type == SDL_KEYUP)
			{
				if (events.key.keysym.sym == SDLK_w)
				{
					keystates[0] = false;
					//runState = 6;
				}
				if (events.key.keysym.sym == SDLK_s)
				{
					keystates[1] = false;
					//runState = 6;
				}
				if (events.key.keysym.sym == SDLK_a)
				{
					keystates[2] = false;
					//runState = 6;
				}
				if (events.key.keysym.sym == SDLK_d)
				{
					keystates[3] = false;
					//runState = 6;
				}
				if (events.key.keysym.sym == SDLK_f)
				{
					keystates[4] = false;
					//fireState = 14;
				}
				if (events.key.keysym.sym == SDLK_SPACE)
				{
					keystates[5] = false;
					//fireState = 14;
				}
			}
		}
		SDL_Delay(100);

		if (lstEnemies->size > 0)
		{
			collisionEnemyTile(lstEnemies, chao);
			printEnemies(lstEnemies, lstBullets, renderer, hero);
			freeEnemies(lstEnemies);
			collisionHeroAgainstEnemy(hero, lstEnemies);
		}

		
		if (lstBullets->size > 0)
		{
			printBullet(lstBullets, renderer);
			freeBullet(lstBullets);
		}
		

		if (lstEnemies->size > 0 && lstBullets->size > 0)
		{
			collisionBulletAgainstEnemy(lstBullets, lstEnemies);
		}
	
		

		for (Tile& t : chao)
		{
			for (int x = 0; x < 40; x++)
			{
				for (int y = 0; y < 30; y++)
				{
					if (map[x][y] == 0)
					{
						t.UpdateTile(renderer, tile[x][y]);
					}

				}
			}
		}

		int i = 0;
		bool collision = false;
		SDL_Rect base;
		base.x = hero->getHeroBox().x;
		base.y = hero->getHeroBox().y + hero->getHeroBox().h/2 + 5;
		base.w = hero->getHeroBox().w - 10;
		base.h = hero->getHeroBox().h / 2 - 5;

		while (i < chao.size() && !checkCollision(chao[i].getTileBox(), base))
		{
				i++;
		}

		if (i < chao.size())
			collision = true;
		
		if (collision)
		{
			hero->setPositionY(chao[i].getPosY() + 4 - hero->getHeroBox().h);
			hero->setOnTheFloor(true);
		}
		else
		{
			hero->setOnTheFloor(false);
		}

		hero->MOVIMENTS_hero(keystates, renderer, &wallCollider);
		SDL_RenderCopy(renderer, mato, NULL, NULL);

		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		//SDL_RenderDrawRect(renderer, &base);
		//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		SDL_RenderPresent(renderer);	
	}
	hero->~Hero();
	freeAll(lstBullets, lstEnemies);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
