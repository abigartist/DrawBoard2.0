#include "cir_factor.h"

void CirFactor::Paint()
{
	Ellipse(hdc, x1, y1, x2, y2);
}

void CirFactor::SetDes(vector<int> buffer)
{
	x1 = buffer[0];
	y1 = buffer[1];
	x2 = buffer[2];
	y2 = buffer[3];
}

void CirFactor::SetDC(HDC hdc_for_set)
{
	hdc = hdc_for_set;
}

void CirFactor::Move(int dx, int dy)
{
	x1 += dx;
	y1 += dy;
	x2 += dx;
	y2 += dy;
}

bool CirFactor::IsChoosed(int x0, int y0)
{
	if ((pow(x0 - x1, 2) + pow(y0 - y1, 2)) < (pow(x2 - x1, 2) + pow(y2 - y1, 2))) {
		return YES;
	}
	return NO;
}

bool CirFactor::HandleMsg(message_for_shapes msg)
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
			else if (IsChoosed(x1_msg, y1_msg)) {
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

bool CirFactor::OverHandle()
{
	return isover_handled;
}

queue<int> CirFactor::OutObjPos()
{
	queue<int> temp;
	temp.push(CIREVENT);
	temp.push(x1);
	temp.push(y1);
	temp.push(x2);
	temp.push(y2);
	temp.push(EVENTEND);
	return temp;
}
