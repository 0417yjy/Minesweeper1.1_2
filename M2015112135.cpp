#include "Common.h"
#include "Point.h"
#include "M2015112135.h"
#include <algorithm>
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
M2015112135::M2015112135()
{
	//보드 정보 초기화
	for (int i = 0; i < BOARD_SIZE; i++)
		for (int j = 0; j < BOARD_SIZE; j++)
			boardInfo[i][j] = -1;
}
Point M2015112135::input()
{
	if (toCheck_queue.size() == 0) {
		//체크 리스트에 원소가 없으면 랜덤으로 위치를 골라 p 리턴 (이 때 미확인한 곳만 리턴)
		int tmp_x, tmp_y;
		tmp_x = rand() % BOARD_SIZE;
		tmp_y = rand() % BOARD_SIZE;
		while (boardInfo[tmp_x][tmp_y] != -1) {
			tmp_x = rand() % BOARD_SIZE;
			tmp_y = rand() % BOARD_SIZE;
		}
		Point p(tmp_x, tmp_y);
		//cout << "Return Random Point: " << tmp_x << ',' << tmp_y << endl;
		return p;
	}
	else {
		//체크 리스트에 원소가 있으면 앞의 원소부터 벡터에서 꺼내 p 리턴
		Point p = (Point)toCheck_queue.front();
		toCheck_queue.pop_front();
		//cout << "Return Point from queue: " << p.getX() << ',' << p.getY() << endl;
		return p;
	}
}

void M2015112135::checkMineInfo(Point p)
{
	boardInfo[p.getX()][p.getY()] = -2;
	searchPointandDelete(p);
}
void M2015112135::checkBoardInfo(Point p, int value)
{
	const int x[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int y[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	boardInfo[p.getX()][p.getY()] = value;
	searchPointandDelete(p);

	//우선순위에 맞추어 값을 집어넣고 정렬
	if (value != 0) {
		for (int i = 0; i < 8; i++) {
			myPoint tmp_p(p.getX() + x[i], p.getY() + y[i], value);
			if (tmp_p.checkBoardRange()) {
				if (boardInfo[tmp_p.getX()][tmp_p.getY()] == -1) {
					boardInfo[tmp_p.getX()][tmp_p.getY()] = -2;
					toCheck_queue.push_back(tmp_p);
				}
				else {
					//기존 큐에 새로 추가할 포인트가 이미 있으면
					//기존 우선순위에 해당 값을 더함
					for (int j = 0; j < toCheck_queue.size(); j++) {
						if (toCheck_queue[j].getX() == tmp_p.getX() && toCheck_queue[j].getY() == tmp_p.getY()) {
							//cout << "Modifying priority in queue: " << tmp_p.getX() <<','<<tmp_p.getY() <<'('<<toCheck_queue[j].getPriority()<<')' <<" to ("<<value<<')' << endl;
							toCheck_queue[j].setPriority(toCheck_queue[j].getPriority() + value);
							break;
						}
					}
				}
			}
		}
	}
	bubble_sort(&toCheck_queue); //안정적 정렬을 위해 버블정렬

	//큐 출력
	// cout << "Checking queue: ";
	// for(int i=0;i<toCheck_queue.size();i++)
	// 	cout << toCheck_queue[i].getX() << ',' << toCheck_queue[i].getY() << '(' << toCheck_queue[i].getPriority() << ") ";
	// cout << endl;

	//지뢰가 확실할 때 우선순위 8로 두고 추가 - 보드판에 비해 지뢰 수가 너무 적어 대부분 하나씩 분포하므로, 공식이 나타나질 않아 구현필요없음
}

void M2015112135::bubble_sort(deque<myPoint> *queue) {
	int i, j;
	myPoint temp(0, 0, 0);
	int flag = 1;
	for (i = queue->size() - 1; flag > 0; i--) {
		flag = 0;
		// 0 ~ i-1 까지 가면서 크기 비교하여 자리 바꿈
		for (j = 0; j < i; j++)
			if ((*queue)[j] < (*queue)[j + 1]) {
				SWAP((*queue)[j], (*queue)[j + 1], temp);
				flag = 1;
			}
	}
}

//큐에 값을 받은 위치가 있으면 해당 원소 삭제
void M2015112135::searchPointandDelete(Point p) {
	for (auto it = toCheck_queue.begin(); it != toCheck_queue.end();) {
		if (p == *it) {
			it = toCheck_queue.erase(it);
			break;
		}
		else
			it++;
	}
}

void myPoint::setPriority(int p) {
	priority = p;
}

int myPoint::getPriority() {return priority;}

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