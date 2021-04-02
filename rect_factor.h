#pragma once
#include "shape_factor.h"

#define YES 1
#define NO 0



class RectFactor :
	public ShapeFactor
{
public:
	RectFactor() = default;
	~RectFactor() = default;
	void Paint() override;   //��ͼ
	void SetDes(vector<int> buffer) override;
	void SetDC(HDC hdc_for_set) override;
	void Move(int dx, int dy) override; //�ƶ�ͼƬ
	bool IsChoosed(int x0, int y0) override; //�ж�ͼƬ�Ƿ�ѡ��
	bool HandleMsg(message_for_shapes msg) override;
	bool OverHandle() override;
	bool IsHaveObj() override;
	queue<int> OutObjPos() override;
private:
	int x1, y1, x2, y2;
	int cx, cy;//��ѡ��Ϊ�ƶ�ʱ��ѡ��ֱ�ߺ�����cx,cy
	bool ischoosed, isover_handled = 0;
	HDC hdc;
};

class RectContainer :
	public ShapeContainer {
public:
	ShapeFactor* NewObj() override {
		ShapeFactor* rect_temp = new RectFactor;
		return rect_temp;
	}
};