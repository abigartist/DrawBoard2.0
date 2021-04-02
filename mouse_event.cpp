#include "mouse_event.h"

void MouseEventFactor::LeftButtonClick()
{
	queue<int> msg_temp;
	x2 = x1 = LOWORD(lParam);
	y2 = y1 = HIWORD(lParam);
	msg_temp.push(x1);
	msg_temp.push(y1);
	msg_to_shape = { SETPOINTSUSPEND,msg_temp ,choice, FALSE };
	loader = 1;
}

void MouseEventFactor::LeftCtrlClick()
{
	queue<int> msg_temp;
	x2 = x1 = LOWORD(lParam);
	y2 = y1 = HIWORD(lParam);
	msg_temp.push(x1);
	msg_temp.push(y1);
	msg_to_shape = { SETPOINTON,msg_temp ,choice, FALSE };
	loader = 1;
}

void MouseEventFactor::LeftButtonDown()
{
	queue<int> msg_temp;
	switch (choice) {
	case MOVEEVENT:
		x2 = x1 = LOWORD(lParam);
		y2 = y1 = HIWORD(lParam);
		msg_temp.push(x1);
		msg_temp.push(y1);
		msg_temp.push(x2);
		msg_temp.push(y2);
		msg_to_shape = { SETPOINTSUSPEND,msg_temp ,choice, FALSE};
		loader = 1;
		break;
	case NULLEVENT:
		break;
	default:
		x1 = LOWORD(lParam);
		y1 = HIWORD(lParam);
		loader = 0;
		break;
	}
}

void MouseEventFactor::LeftButtonUp()
{
	queue<int> msg_temp;
	switch (choice) {
	case MOVEEVENT:
		x2 = x1 = LOWORD(lParam);
		y2 = y1 = HIWORD(lParam);
		msg_temp.push(x1);
		msg_temp.push(y1);
		msg_temp.push(x2);
		msg_temp.push(y2);
		msg_to_shape = { SETPOINTOFF,msg_temp,choice ,FALSE };
		loader = 1;
		break;
	case NULLEVENT:
		break;
	default:
		x2 = LOWORD(lParam);
		y2 = HIWORD(lParam);
		if (PointDis(x1, y1, x2, y2) < 10) {
			LeftButtonClick();
			break;
		}
		msg_temp.push(x1);
		msg_temp.push(y1);
		msg_temp.push(x2);
		msg_temp.push(y2);
		msg_to_shape = { SETPOINTON,msg_temp,choice ,FALSE };
		loader = 1;
		break;
	}
}

void MouseEventFactor::MouseMoving()
{
	queue<int> msg_temp;
	if (choice == MOVEEVENT && wParam == MK_LBUTTON) {
		x2 = x1 = LOWORD(lParam);
		y2 = y1 = HIWORD(lParam);
		msg_temp.push(x1);
		msg_temp.push(y1);
		msg_temp.push(x2);
		msg_temp.push(y2);
		msg_to_shape = { SETPOINTSUSPEND,msg_temp ,choice ,TRUE};
		loader = 1;
	}
	else loader = 0;
}

double MouseEventFactor::PointDis(int posx1, int posy1, int posx2, int posy2)
{
	return sqrt(pow((double)posx1 - (double)posx2, 2) + pow((double)posy1 - (double)posy2, 2));
}

bool MouseEventFactor::IsLoader()
{
	return loader;
}


message_for_shapes MouseEventFactor::GetEvent(UINT msg, WPARAM wParam, LPARAM lParam, Choice choice)
{
	MouseEventFactor::msg = msg;
	MouseEventFactor::wParam = wParam;
	MouseEventFactor::lParam = lParam;
	MouseEventFactor::choice = choice;
	MouseEventSelector();
	return msg_to_shape;
}

void MouseEventFactor::MouseEventSelector()
{
	switch (msg) 
	{
	case WM_LBUTTONDOWN:
		LeftButtonDown();
		if (wParam & MK_CONTROL) {
			LeftCtrlClick();
		}
		break;
	case WM_LBUTTONUP:
		LeftButtonUp();
		break;
	case WM_MOUSEMOVE: 
		MouseMoving();
		break;
	default:
		break;
	}

}
