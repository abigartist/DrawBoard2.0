#include "mousemsg.h"
#include "record.h"

extern RecordStack MainStack;

void MouseCallback(HWND& hWnd, UINT message, WPARAM wParam, LPARAM lParam,int choice)
{
	static int x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, flag = 0, choosedX = 0, choosedY = 0, dX = 0, dY = 0;
	HDC hdc;
	switch (message) {
	case WM_LBUTTONDOWN:
		switch (choice)
		{
		case LINE:
			flag = 0;
			x1 = LOWORD(lParam);
			y1 = HIWORD(lParam);
			break;
		case MOVE:
			choosedX = LOWORD(lParam);
			choosedY = HIWORD(lParam);
			flag = MainStack.clicked(choosedX, choosedY);
			break;
		case RECT:
			flag = 0;
			x1 = LOWORD(lParam);
			y1 = HIWORD(lParam);
			break;
		default:
			break;
		}
		break;
	case WM_LBUTTONUP:
		switch (choice)
		{
		case LINE:
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			if (x1 != x2 || y1 != y2)
			{
				MainStack.push(LINE, x1, y1, x2, y2, 0, 0);
				hdc = GetDC(hWnd);
				MoveToEx(hdc, x1, y1, nullptr);
				LineTo(hdc, x2, y2);
				ReleaseDC(hWnd, hdc);
			}
			break;
		case MOVE:
			if(choosedX!=LOWORD(lParam)||choosedY!=HIWORD(lParam))
			    flag = 0;
			break;
		case RECT:
			x2 = LOWORD(lParam);
			y2 = HIWORD(lParam);
			if (x1 != x2 || y1 != y2) {
				MainStack.push(RECT, x1, y1, x2, y2, 0, 0);
				hdc = GetDC(hWnd);
				Rectangle(hdc, x1, y1, x2, y2);
				ReleaseDC(hWnd, hdc);
			}
			break;
		default:
			break;
		}
		break;
	case WM_MOUSEMOVE:
		if (flag == 1 && wParam == MK_LBUTTON) {//选中图形且没有松手
			dX = LOWORD(lParam) - choosedX;
			choosedX = LOWORD(lParam);
			//dX = 200;
			dY = HIWORD(lParam) - choosedY;
			choosedY = HIWORD(lParam);
			if (dX || dY) {
				MainStack.AddDx(dX, dY);
				//UpdateWindow(hWnd);
				InvalidateRect(hWnd, nullptr, TRUE);
			}
			break;
		}
		break;
	default:
		break;
	}
}
