#include "pol_factor.h"

void PolFactor::Paint()
{
	if (isover_handled) {
		for (int index = 0; index < pos.size() - 3; index += 2) {
			MoveToEx(hdc, pos[index], pos[index + 1], nullptr);
			LineTo(hdc, pos[index + 2], pos[index + 3]);
		}
		MoveToEx(hdc, pos[pos.size() - 2], pos[pos.size() - 1], nullptr);
		LineTo(hdc, pos[0], pos[1]);
	}
}

void PolFactor::SetDes(vector<int> buffer)
{
	pos = buffer;
}

void PolFactor::SetDC(HDC hdc_for_set)
{
	hdc = hdc_for_set;
}

void PolFactor::Move(int dx, int dy)
{
	for (int index = 0; index < pos.size()-1; index += 2) {
		pos[index] += dx;
		pos[index + 1] += dy;
	}
}

bool PolFactor::OverHandle()
{
	return isover_handled;
}

queue<int> PolFactor::OutObjPos()
{
	queue<int> temp;
	for (int index = 0; index < pos.size(); index++) {
		temp.push(pos[index]);
	}
	return temp;
}
