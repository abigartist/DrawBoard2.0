#pragma once
#include "shape_factor.h"

#define YES 1
#define NO 0

class CirFactor :
	public ShapeFactor
{
public:
	CirFactor() = default;
	~CirFactor() = default;
	void Paint() override;   //��ͼ
	void SetDes(vector<int> buffer) override;
	void SetDC(HDC hdc_for_set) override;
	void Move(int dx, int dy) override; //�ƶ�ͼƬ
	bool IsChoosed(int x0, int y0) override; //�ж�ͼƬ�Ƿ�ѡ��
	bool HandleMsg(message_for_shapes msg) override;
	bool IsHaveObj() override;
	bool OverHandle() override;
	queue<int> OutObjPos() override;
private:
	int x1, y1, x2, y2;
	int cx, cy;//��ѡ��Ϊ�ƶ�ʱ��ѡ��ֱ�ߺ�����cx,cy
	bool ischoosed, isover_handled = 0;
	HDC hdc;
};

class CirContainer :
	public ShapeContainer {
public:
	ShapeFactor* NewObj() {
		ShapeFactor* cir_temp = new CirFactor;
		return cir_temp;
	}
};