#pragma once
#include "shape_factor.h"

#define YES 1
#define NO 0
#define MAGICNUM 999

class PolFactor :
	public ShapeFactor
{
public:
	PolFactor() = default;
	~PolFactor() = default;
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
	vector<int> pos;
	int cx, cy;//��ѡ��Ϊ�ƶ�ʱ��ѡ��ֱ�ߺ�����cx,cy
	bool start_point = 0;
	bool ischoosed, isover_handled = 0;
	HDC hdc;
};

class PolContainer :
	public ShapeContainer {
public:
	ShapeFactor* NewObj() {
		ShapeFactor* pol_temp = new PolFactor;
		return pol_temp;
	}
};

