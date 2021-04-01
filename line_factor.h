#pragma once

#include "shape_factor.h"
#include <cmath>

#define YES 1
#define NO 0

class LineFactor :
	public ShapeFactor
{
public:
	LineFactor()=default;
	~LineFactor() = default;
	void Paint() override;   //绘图
	void SetDes(vector<int> buffer) override;
	void SetDC(HDC hdc_for_set) override;
	void Move(int dx,int dy) override; //移动图片
	bool IsChoosed(int x0,int y0) override; //判断图片是否被选中
	bool HandleMsg(message_for_shapes msg) override;
	bool OverHandle() override;
	queue<int> OutObjPos() override;
private:
	int x1, y1, x2, y2;
	int cx, cy;//当选项为移动时，选中直线后启用cx,cy
	bool ischoosed, isover_handled = 0;;
	HDC hdc;
};

class LineContainer :
	public ShapeContainer {
public:
	ShapeFactor* NewObj() {
		ShapeFactor* line_temp = new LineFactor;
		return line_temp;
	}
};