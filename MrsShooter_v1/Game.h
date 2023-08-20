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
using namespace HeroClass;
using namespace EnemyClass;
using namespace TILES;

void close();

#endif