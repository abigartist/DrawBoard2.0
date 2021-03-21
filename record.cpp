#include "record.h"
#include "calculate.h"


RecordStack::RecordStack()
{
	rep(MAX_SHAPE - 1) {
		array[index].shape = 0;
		array[index].x1 = 0;
		array[index].y1 = 0;
		array[index].x2 = 0;
		array[index].y2 = 0;
		array[index].x3 = 0;
		array[index].y3 = 0;
	}
	int StackTop = 0;
}

int RecordStack::push(int shape, int x1, int y1, int x2, int y2, int x3, int y3) {
	switch (shape) {
	case LINE:
		array[StackTop].shape = LINE;
		array[StackTop].x1 = x1;
		array[StackTop].y1 = y1;
		array[StackTop].x2 = x2;
		array[StackTop].y2 = y2;
		break;
	case RECT:
		array[StackTop].shape = RECT;
		array[StackTop].x1 = x1;
		array[StackTop].y1 = y1;
		array[StackTop].x2 = x2;
		array[StackTop].y2 = y2;
		break;
	case CIR:
		array[StackTop].shape = CIR;
		array[StackTop].x1 = x1;
		array[StackTop].y1 = y1;
		array[StackTop].x2 = x2;
		array[StackTop].y2 = y2;
		break;
	}
	StackTop++;
	return 1;
}

int RecordStack::GetStackTop()
{
	return StackTop;
}

DesAndShape RecordStack::OutPoint(int index)
{
	return array[index];
}

void RecordStack::AddDx(int dx, int dy)
{
	array[StackTop-1].x1 += dx;
	array[StackTop-1].y1 += dy;
	array[StackTop-1].x2 += dx;
	array[StackTop-1].y2 += dy;
}

/*void RecordStack::change(int index, int shape,int x1, int y1, int x2, int y2)
{
	array[index].shape = shape;
	array[index].x1 = x1;
	array[index].y1 = y1;
	array[index].x2 = x2;
	array[index].y2 = y2;
	StackTop++;
}
*/
void RecordStack::swap(int index1, int index2)
{
	if (index1 == index2) {
		return;
	}
	rep_2(index1, index2) {
		DesAndShape temp;
		temp = array[index + 1];
		array[index + 1] = array[index];
		array[index] = temp;
	}
}
bool RecordStack::clicked(int x, int y)
{
	int flag = 0;
	repop(StackTop) {
		switch (array[index].shape)
		{
		case LINE://数学方法判断热点是否在直线范围内
			if (IsInLineRange((double)x, (double)y, (double)array[index].x1, (double)array[index].y1, (double)array[index].x2, (double)array[index].y2)) {
				swap(index, StackTop-1);
				flag = 1;
				break;
			}
		    break;
		case RECT:
			if (IsInRectRange(x, y, array[index].x1, array[index].y1, array[index].x2, array[index].y2)) {
				swap(index, StackTop - 1);
				flag = 1;
				break;
			}
			break;
		case CIR:
			if (IsInCirRange(x, y, array[index].x1, array[index].y1, array[index].x2, array[index].y2)) {
				swap(index, StackTop - 1);
				flag = 1;
				break;
			}
			break;
		default:
			break;
		}
		if (flag) return true;
	}
	return false;
}
/*
if (((double)y - (double)array[index].y1) / ((double)array[index].y2 - (double)array[index].y1) < ((double)array[index].x2 - (double)array[index].x1 + 10) && ((double)y - (double)array[index].y1) / ((double)array[index].y2 - (double)array[index].y1) > ((double)array[index].x2 - (double)array[index].x1 - 10)) {
				swap(index, StackTop);//打印时从栈顶向下打印，将index冒泡至栈顶
				break;
			}
*/