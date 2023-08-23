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
	std::vector<Tile> chao;

	auto map = new int[30][80];
	auto tile = new SDL_Rect[30][80];

	SDL_Rect rect;
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			rect.y = y * 16;
			rect.x = x * 16;
			rect.w = 16;
			rect.h = 16;
			tile[y][x] = rect;
		}
	}

	ifstream inputFile;
	inputFile.open("maps/mapV0.csv");


	if (inputFile.is_open())
	{ 
		string line;
		int x = 0;
		int y = 0;

		while (getline(inputFile, line))
		{
			stringstream stream(line);
			string chunk;
			x = 0;
			while (getline(stream, chunk, ',') && x < 80)
			{
				map[y][x] = stoi(chunk);

				 if (map[y][x] == 59)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 59, renderer));
				 }
				 else if (map[y][x] == 150)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 150, renderer));
				 }
				 else if (map[y][x] == 151)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 151, renderer));
				 }
				 else if (map[y][x] == 163)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 163, renderer));
				 }
				 else if (map[y][x] == 164)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 164, renderer));
				 }
				 x++;
			}
			y++;
		}
	}

	inputFile.close();

	SDL_Rect wallCollider; 
	wallCollider.x = 0;
	wallCollider.y = 0;
	wallCollider.w = SCREEN_WIDTH;
	wallCollider.h = SCREEN_HEIGHT;

	Hero* hero = new Hero(200, 100, renderer);

	LISTBullets* lstBullets = createList();
	LISTEnemies* lstEnemies = createListOfEnemies();

	insertEnemies(lstEnemies, renderer, 400, 100);
	insertEnemies(lstEnemies, renderer, 500, 100);

	bool isRunning = true;
	bool keystates[6] = { false };

	//SDL_Texture* background3 = loadTexture(renderer, "maps/nuvens_3.png", NULL, NULL);
	//SDL_Texture* background2 = loadTexture(renderer, "maps/nuvens_2.png", NULL, NULL);
	//SDL_Texture* background1 = loadTexture(renderer, "maps/nuvens_1.png", NULL, NULL);


	Timer fpsTimer = Timer();
	Timer capTimer = Timer();

	int countedFrames = 0;
	double avgFrames = 0.0;
	fpsTimer.Start();

	
	while(isRunning)
	{
		capTimer.Start();

		double timerDebug = (fpsTimer.getTicks() / 1000 * 1.0);
		avgFrames = countedFrames / (fpsTimer.getTicks() / 1000 * 1.0);
		if (avgFrames > 2000000)
		{
			avgFrames = 0;
		}

		//std::cout << avgFrames << "\n";
		//DEFAULT (IDLE)
		SDL_RenderClear(renderer);

		//SDL_RenderCopy(renderer, background3, NULL, NULL);
		//SDL_RenderCopy(renderer, background2, NULL, NULL);
		//SDL_RenderCopy(renderer, background1, NULL, NULL);
		
		if (hero->getLife() > 0 && lstEnemies->size < 3)
		{
			insertEnemies(lstEnemies, renderer, rand() % 600 + 1, rand() % 400 + 1);
			insertEnemies(lstEnemies, renderer, rand() % 600 + 1, rand() % 400 + 1);
		}

		SDL_Event events;

		while (SDL_PollEvent(&events))
		{
			if (events.type == SDL_QUIT)
			{
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
	
		collisionHeroTile(chao, hero, renderer);

		vector<Tile>::iterator it;
			for (int y = 0; y < 30; y++)
			{
				for (int x = 0; x < 40; x++)
				{
					for(it = chao.begin(); it != chao.end(); it++)
					{
						if (map[y][x] == it->getType())
						{
							it->UpdateTile(renderer, tile[y][x]);
							break;
						}
					}
				}
			}

		hero->MOVIMENTS_hero(keystates, renderer, &wallCollider);
		//SDL_RenderCopy(renderer, mato, NULL, NULL);

		SDL_RenderPresent(renderer);	
		countedFrames++;

		///// frame cap
		int framesTicks = capTimer.getTicks();
		if (framesTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - framesTicks);
		}
		//std::cout << avgFrames << "\n";
		/////	
	}
	hero->~Hero();
	freeAll(lstBullets, lstEnemies);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
