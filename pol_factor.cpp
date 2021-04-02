#include "pol_factor.h"

void PolFactor::Paint()
{
	if (isover_handled) {
		for (int index = 0; index < pos.size() - 3; index += 2) {
			MoveToEx(hdc, pos[index], pos[index + 1], nullptr);
			LineTo(hdc, pos[index + 2], pos[index + 3]);
		}
		MoveToEx(hdc, pos[pos.size() - 2], pos[pos.size() - 1], nullptr);
		LineTo(hdc, pos[0], pos[1]);
	}
}

void PolFactor::SetDes(vector<int> buffer)
{
	pos = buffer;
}

void PolFactor::SetDC(HDC hdc_for_set)
{
	hdc = hdc_for_set;
}

void PolFactor::Move(int dx, int dy)
{
	for (int index = 0; index < pos.size()-1; index += 2) {
		pos[index] += dx;
		pos[index + 1] += dy;
	}
}

bool PolFactor::IsChoosed(int x0, int y0)
{
	int minx = MAGICNUM, miny = MAGICNUM, maxx = -1, maxy = -1;
	for (int index = 0; index < pos.size()-1; index++) {
		if (pos[index] < minx) {
			minx = pos[index];
		}
		if (pos[index] > maxx) {
			maxx = pos[index];
		}
		if (pos[index + 1] < miny) {
			miny = pos[index + 1];
		}
		if (pos[index + 1] > maxy) {
			maxy = pos[index + 1];
		}
	}
	if (x0<maxx && x0>minx && y0<maxy && y0>miny) {
		return YES;
	}
	else return NO;
}

bool PolFactor::HandleMsg(message_for_shapes msg)
{
	if (isover_handled) {//isoverhandled如果等于1，说明已经完成了各点坐标的定义，可以像其他图形一样进行操作
		int x1_msg, y1_msg, x2_msg, y2_msg;
		x1_msg = msg.pos.front();
		msg.pos.pop();
		y1_msg = msg.pos.front();
		msg.pos.pop();

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
	}else{
		switch (msg.event_msg) {
		case SETPOINTON:
			if (start_point) {
				pos.push_back(msg.pos.front());
				msg.pos.pop();
				pos.push_back(msg.pos.front());
				msg.pos.pop();
			}
			isover_handled = start_point;
			start_point = !start_point;
			return TRUE;
			break;
		case SETPOINTOFF:
			return FALSE;
			break;
		case SETPOINTSUSPEND:
			pos.push_back(msg.pos.front());
			msg.pos.pop();
			pos.push_back(msg.pos.front());
			msg.pos.pop();
			return FALSE;
			break;
		}
	}
}

bool PolFactor::OverHandle()
{
	return isover_handled;
}

bool PolFactor::IsHaveObj()
{
	return start_point;
}

queue<int> PolFactor::OutObjPos()
{
	queue<int> temp;
	for (int index = 0; index < pos.size(); index++) {
		temp.push(pos[index]);
	}
	return temp;
}
