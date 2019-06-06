#ifndef M2015112135_H
#define M2015112135_H
#include "Common.h"
#include "Player.h"
#include <deque>

//큐에 우선순위를 두기 위해 Point에서 상속받아 새 클래스 생성
class myPoint : public Point {
	int priority; //우선순위는 주위 숫자칸 중에서 가장 큰 값을 우선순위로 설정
public:
	myPoint(int x, int y, int priority) : Point(x, y) {
		this->priority = priority;
	}
	void setPriority(int p);
	bool myPoint::operator < (const myPoint &a);
	bool myPoint::operator > (const myPoint &a);
};

class M2015112135 : public Player
{
	//보드의 정보가 나타날 때마다 저장
	//-1: 미확인, -2: 지뢰, 0~8: 주변 지뢰의 수
	int boardInfo[BOARD_SIZE][BOARD_SIZE];
	deque<myPoint> toCheck_queue;
public:
	M2015112135();
	Point input();
	void checkMineInfo(Point p);
	void checkBoardInfo(Point p, int value);
	void bubble_sort(deque<myPoint> *queue);
};
#endif