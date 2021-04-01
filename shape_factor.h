#pragma once



#include "mouse_event.h"
#include <vector>
#include <queue>

#define EVENTEND -1

using std::queue;
using std::vector;

class ShapeFactor
{
public:
	virtual queue<int> OutObjPos() = 0;
	virtual void Paint() = 0;   //绘图,注意必须在WM_PAINT中使用
	virtual void SetDC(HDC hdc_for_set) = 0;
	virtual void SetDes(vector<int> buffer) = 0;
	virtual void Move(int dx, int dy) = 0; //移动图片
	virtual bool OverHandle() = 0;
	virtual bool IsChoosed(int x0, int y0) = 0; //判断图片是否被选中
	virtual bool HandleMsg(message_for_shapes msg) = 0; //任何使用该接口的类必须实现消息处理机制
};

class ShapeContainer {
public:
	virtual ShapeFactor* NewObj() = 0;//需要在各个类里面定义此项
};

