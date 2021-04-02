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
	virtual void Paint() = 0;   //��ͼ,ע�������WM_PAINT��ʹ��
	virtual void SetDC(HDC hdc_for_set) = 0;
	virtual void SetDes(vector<int> buffer) = 0;
	virtual void Move(int dx, int dy) = 0; //�ƶ�ͼƬ
	virtual bool OverHandle() = 0;
	virtual bool IsChoosed(int x0, int y0) = 0; //�ж�ͼƬ�Ƿ�ѡ��
	virtual bool IsHaveObj() = 0;//�ж�Ŀǰ�Ƿ���������Ķ���
	virtual bool HandleMsg(message_for_shapes msg) = 0; //�κ�ʹ�øýӿڵ������ʵ����Ϣ�������
};

class ShapeContainer {
public:
	virtual ShapeFactor* NewObj() = 0;//��Ҫ�ڸ��������涨�����
};

