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
	void Paint() override;   //绘图
	void SetDes(vector<int> buffer) override;
	void SetDC(HDC hdc_for_set) override;
	void Move(int dx, int dy) override; //移动图片
	bool IsChoosed(int x0, int y0) override; //判断图片是否被选中
	bool HandleMsg(message_for_shapes msg) override;
	bool OverHandle() override;
	bool IsHaveObj() override;
	queue<int> OutObjPos() override;
private:
	vector<int> pos;
	int cx, cy;//当选项为移动时，选中直线后启用cx,cy
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

