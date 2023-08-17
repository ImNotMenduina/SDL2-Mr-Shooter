#pragma once
#include "Entities.h"
class CactusEnemy : public Entities
{
private:

public:
	CactusEnemy();
	CactusEnemy(int posx, int posy);
	void setPositionX(int posx);
	void setPositionY(int posy);
	int getPositionX();
	int getPositionY();
	~CactusEnemy() {};
};
