#include "Game.h"
#include <unordered_map>

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

	std::unordered_map<int, Tile> Tiles;

	std::vector<Tile> chao;
	vector<Tile>::iterator it;

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
					 Tiles.insert({ 59, Tile(y * 16, x * 16, 59, renderer) });
				 }
				 else if (map[y][x] == 150)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 150, renderer));
					 Tiles.insert({ 150, Tile(y * 16, x * 16, 150, renderer) });
				 }
				 else if (map[y][x] == 151)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 151, renderer));
					 Tiles.insert({ 151, Tile(y * 16, x * 16, 151, renderer) });

				 }
				 else if (map[y][x] == 163)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 163, renderer));
					 Tiles.insert({ 163, Tile(y * 16, x * 16, 163, renderer) });
				 }
				 else if (map[y][x] == 164)
				 {
					 chao.push_back(Tile(y * 16, x * 16, 164, renderer));
					 Tiles.insert({ 164, Tile(y * 16, x * 16, 164, renderer) });
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

	bool isRunning = true;
	bool keystates[6] = { false };

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

		//DEFAULT (IDLE)
		SDL_RenderClear(renderer);
		
		if (hero->getLife() > 0 && lstEnemies->size < 2)
		{
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

		collisionEnemyTile(lstEnemies, chao);
		printEnemies(lstEnemies, lstBullets, renderer, hero);
		freeEnemies(lstEnemies);
		collisionHeroAgainstEnemy(hero, lstEnemies);

		printBullet(lstBullets, renderer);
		freeBullet(lstBullets);

		collisionBulletAgainstEnemy(lstBullets, lstEnemies);

		collisionHeroTile(chao, hero, renderer);

		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 80; x++)
			{
				int n = map[y][x];

				if (n > 0)
				{
					if (n == 59)
						Tiles.at(59).UpdateTile(renderer, tile[y][x]);
					else if (n == 150)
						Tiles.at(150).UpdateTile(renderer, tile[y][x]);
					else if (n == 151)
						Tiles.at(151).UpdateTile(renderer, tile[y][x]);
					else if (n == 163)
						Tiles.at(163).UpdateTile(renderer, tile[y][x]);
					else if (n == 164)
						Tiles.at(164).UpdateTile(renderer, tile[y][x]);
				}
			}
		}

		std::cout << Tiles.size() << "\n";

		hero->MOVIMENTS_hero(keystates, renderer, &wallCollider);

		SDL_RenderPresent(renderer);	
		countedFrames++;

		///// frame cap
		int framesTicks = capTimer.getTicks();
		if (framesTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - framesTicks);
		}
		/////	
	}
	hero->~Hero();
	freeAll(lstBullets, lstEnemies);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
