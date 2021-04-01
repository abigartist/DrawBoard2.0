#include "line_factor.h"

/*LineFactor::LineFactor(int x1, int y1, int x2, int y2)
{
	LineFactor::x1 = x1;
	LineFactor::y1 = y1;
	LineFactor::x2 = x2;
	LineFactor::y2 = y2;
}*/

void LineFactor::Paint()
{
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}

void LineFactor::SetDes(vector<int> buffer)
{
	x1 = buffer[0];
	y1 = buffer[1];
	x2 = buffer[2];
	y2 = buffer[3];
}

void LineFactor::SetDC(HDC hdc_for_set)
{
	hdc = hdc_for_set;
}


void LineFactor::Move(int dx, int dy)
{
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

bool LineFactor::IsChoosed(int x0,int y0)
{
	double k = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);
	double b = (double)y2 - k * (double)x2;
	double d = fabs(k * (double)x0 + b - (double)y0) / sqrt(pow(k, 2) + 1);
	return d < 10 ? YES : NO;
}

bool LineFactor::HandleMsg(message_for_shapes msg)
{
	int x1_msg, y1_msg, x2_msg, y2_msg;
	while (!msg.pos.empty()) {
		x1_msg = msg.pos.front();
		msg.pos.pop();
		y1_msg = msg.pos.front();
		msg.pos.pop();
		x2_msg = msg.pos.front();
		msg.pos.pop();
		y2_msg = msg.pos.front();
		msg.pos.pop();
	}
	while (TRUE) {
		switch (msg.event_msg)
		{
		case SETPOINTSUSPEND:
			if (ischoosed) msg.event_msg = SETPOINTON;
			else if(IsChoosed(x1_msg,y1_msg)){
				ischoosed = TRUE;
				cx = x1_msg;
				cy = y1_msg;
				msg.event_msg = SETPOINTON;
			}
			else {
				msg.event_msg = SETPOINTOFF;
			}
			break;
		case SETPOINTOFF:
			ischoosed = FALSE;
			return FALSE;
		case SETPOINTON:
			Move(x1_msg - cx, y1_msg - cy);
			cx = x1_msg;
			cy = y1_msg;
			return TRUE;
		default:
			break;
		}
	}
	isover_handled = 1;
}

bool LineFactor::OverHandle()
{
	return isover_handled;
}

queue<int> LineFactor::OutObjPos()
{
	queue<int> temp;
	temp.push(LINEEVENT);
	temp.push(x1);
	temp.push(y1);
	temp.push(x2);
	temp.push(y2);
	temp.push(EVENTEND);
	return temp;
}
