#ifndef M2012345678_H
#define M2012345678_H
#include "Common.h"
#include "Player.h"
class M2012345678 : public Player
{
public :
	M2012345678();
	Point input();
	void checkMineInfo(Point p);
	void checkBoardInfo(Point p, int value);
};
#endif