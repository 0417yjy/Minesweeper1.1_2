#ifndef M2015112135_H
#define M2015112135_H
#include "Common.h"
#include "Player.h"
#include <deque>

//ť�� �켱������ �α� ���� Point���� ��ӹ޾� �� Ŭ���� ����
class myPoint : public Point {
	int priority; //�켱������ ���� ����ĭ �߿��� ���� ū ���� �켱������ ����
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
	//������ ������ ��Ÿ�� ������ ����
	//-1: ��Ȯ��, -2: ����, 0~8: �ֺ� ������ ��
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