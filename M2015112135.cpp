#include "Common.h"
#include "Point.h"
#include "M2015112135.h"
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
M2015112135::M2015112135()
{
	//���� ���� �ʱ�ȭ
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			boardInfo[i][j] = -1;
}
Point M2015112135::input()
{
	if (toCheck_queue.size() == 0) {
		//üũ ����Ʈ�� ���Ұ� ������ �������� ��ġ�� ��� p ���� (�� �� ��Ȯ���� ���� ����)
		int tmp_x, tmp_y;
		tmp_x = rand() % BOARD_SIZE;
		tmp_y = rand() % BOARD_SIZE;
		while (boardInfo[tmp_x][tmp_y] != -1) {
			tmp_x = rand() % BOARD_SIZE;
			tmp_y = rand() % BOARD_SIZE;
		}
		Point p(tmp_x, tmp_y);
		return p;
	}
	else {
		//üũ ����Ʈ�� ���Ұ� ������ ���� ���Һ��� ���Ϳ��� ���� p ����
		Point p = (Point)toCheck_queue.front();
		toCheck_queue.pop_front();
		return p;
	}
}

void M2015112135::checkMineInfo(Point p)
{
	boardInfo[p.getX()][p.getY()] = -2;
	//ť�� ���� ��ġ�� ������ �ش� ���� ����
	for (auto it = toCheck_queue.begin(); it != toCheck_queue.end();) {
		if (p == *it) {
			it = toCheck_queue.erase(it);
			break;
		}
		else
			it++;
	}
}
void M2015112135::checkBoardInfo(Point p, int value)
{
	const int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	//�켱������ ���߾� ���� ����ְ� ����
	boardInfo[p.getX()][p.getY()] = boardInfo[p.getX()][p.getY()] < value ? value : boardInfo[p.getX()][p.getY()];
	if (value != 0) {
		for (int i = 0; i < 8; i++) {
			myPoint tmp_p(p.getX() + x[i], p.getY() + y[i], value);
			if (tmp_p.checkBoardRange()) {
				if (boardInfo[tmp_p.getX()][tmp_p.getY()] == -1) {
					toCheck_queue.push_back(tmp_p);
				}
				else if (boardInfo[tmp_p.getX()][tmp_p.getY()] < value) { //������ �켱�������� �� ���� ���̶��
					//�� ���� ������ ����
					for (int j = 0; j < toCheck_queue.size(); j++) {
						if (toCheck_queue[j].getX() == tmp_p.getX() && toCheck_queue[j].getY() == tmp_p.getY()) {
							toCheck_queue[j].setPriority(value);
							break;
						}
					}
				}
			}
		}
	}
	bubble_sort(&toCheck_queue); //������ ������ ���� ��������

	//���ڰ� Ȯ���� �� �켱���� 8�� �ΰ� �߰�
}

void M2015112135::bubble_sort(deque<myPoint> *queue) {
	int i, j;
	myPoint temp(0, 0, 0);
	int flag = 1;
	for (i = queue->size() - 1; flag > 0; i--) {
		flag = 0;
		// 0 ~ i-1 ���� ���鼭 ũ�� ���Ͽ� �ڸ� �ٲ�
		for (j = 0; j < i; j++)
			if ((*queue)[j] > (*queue)[j + 1]) {
				SWAP((*queue)[j], (*queue)[j + 1], temp);
				flag = 1;
			}
	}
}

void myPoint::setPriority(int p) {
	priority = p;
}

bool myPoint::operator < (const myPoint &a) {
	if (this->priority < a.priority)
		return true;
	else
		return false;
}
bool myPoint::operator > (const myPoint &a) {
	if (this->priority > a.priority)
		return true;
	else
		return false;
}