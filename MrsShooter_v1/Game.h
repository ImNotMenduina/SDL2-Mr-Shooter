#ifndef Game_H
#define Game_H

#include<iostream>
//#include<fstream>
//#include<sstream>
//#include<string>
#include <SDL.h>
#include<SDL_image.h>
#include <vector>

#include "Lists.h"
#include "Screen.h"
#include "collision.h"
#include "Tile.h"
#include "Timer.h"
#include "Hero.h"
#include "Enemy.h"

using namespace std;
using namespace TimerClass;
using namespace TileClass;
using namespace HeroClass;
using namespace EnemyClass;

const int SCREEN_FPS = 20;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

#endif