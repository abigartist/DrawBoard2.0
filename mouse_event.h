#pragma once

#include "framework.h"
#include "DrawBoard.h"

#define POINTNUM 100
#include <queue>

using std::queue;

enum  Events
{
	SETPOINTON,//传递的事件仅存设置点的真假，确保鼠标事件的修改不影响使用它的类
	SETPOINTOFF,
	SETPOINTSUSPEND, //当移动时，点实际上是挂起的
};

typedef struct {
	Events event_msg;
	queue<int> pos;
	Choice option;
	bool is_pressed=FALSE;
}message_to_shape_factor, message_for_shapes;


class MouseEventFactor
{
public:
	bool IsLoader();
	message_to_shape_factor msg_to_shape;
	MouseEventFactor() = default;
	~MouseEventFactor() = default;
	message_to_shape_factor GetEvent(UINT msg, WPARAM wParam, LPARAM lParam, Choice choice);
private:
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
	Choice choice;
	int x1, y1, x2, y2, loader = 0;// holding = 0;//loader用于判断当前是否有消息传递必要；holding检测是否还在连续点击中
	void MouseEventSelector();
	void LeftButtonClick();
	void LeftDoubleClick();
	void LeftButtonDown();
	void LeftButtonUp();
	void MouseMoving();
	double PointDis(int posx1, int posy1, int posx2, int posy2);
};

