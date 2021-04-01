// DrawBoard.cpp : 定义应用程序的入口点。
//
//后续为“//”的为后续清除项
#include "framework.h"
//#include "DrawBoard.h"
#include "record_factor.h"
#include <fstream>

//void DrawLine(HWND hWnd);
#define MAX_LOADSTRING 100
#define MAX_PATHLENGTH 50
#define DATAEND -2

// 全局变量:
MouseEventFactor MouseEvent;
RecordFactor MainRecord;
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
WCHAR wrFilePath[MAX_PATHLENGTH];                // 所允许的最长文件路径
int slFlag = 0;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Load(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Save(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DRAWBOARD, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWBOARD));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWBOARD));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DRAWBOARD);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR szBuffer[128];
	HDC hdc;
	size_t iTarget;
	static Choice option=Choice::NULLEVENT;
	static int choice = 0;
	static message_for_shapes temp;
	if (message == WM_MOUSEMOVE || message == WM_LBUTTONDOWN || message == WM_LBUTTONUP) {
		//MouseCallback(hWnd, message, wParam, lParam,choice);//
		MainRecord.GetWnd(hWnd);
		temp = MouseEvent.GetEvent(message, wParam, lParam, option);
		if (MouseEvent.IsLoader()) {
			MainRecord.RespondEvent(temp);
		}
		
	}
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_LOAD:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_LOAD), hWnd, Load);
				InvalidateRect(hWnd, nullptr, TRUE);
				break;
			case IDM_SAVE:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_SAVE), hWnd, Save);
				break;
			case ID_LINE:
				option = Choice::LINEEVENT;
				break;
			case ID_MOVE:
				option = Choice::MOVEEVENT;
				break;
			case ID_RECT:
				option = Choice::RECTEVENT;
				break;
			case ID_CIR:
				option = Choice::CIREVENT;
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			MainRecord.GetWndDC(hdc);
			MainRecord.PaintEvent();
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	//case WM_SIZE:
		//hdc = GetDC(hWnd);
		//StringCchPrintf(szBuffer, 128, TEXT("%d*%d px"), LOWORD(lParam), HIWORD(lParam));
		//StringCchLength(szBuffer, 128, &iTarget);
		//TextOut(hdc, 10, 10, szBuffer, iTarget);
		//ReleaseDC(hWnd, hdc);
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Load(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	HWND hStaticText;
	message_for_shapes msg_from_file;
	switch (message)
	{
	case WM_INITDIALOG:
		hStaticText = GetDlgItem(hDlg, IDC_STATIC);
		SetWindowText(hStaticText, TEXT("在下方对话框输入文件路径以读取文件"));
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK) {
				FILE* fin;
				GetDlgItemText(hDlg, IDC_EDIT1, wrFilePath, MAX_PATHLENGTH);
				_bstr_t b(wrFilePath);//wchar使用此宏转换
				char* file_path;
				file_path = b;
				fopen_s(&fin, file_path, "r+");
				while (TRUE) {
					Choice choice_from_msg = NULLEVENT;
					int end_check;
					fscanf_s(fin, "%d", &end_check);
					if (end_check == DATAEND) {
						break;
					}
					else {
						choice_from_msg = (Choice)end_check;
						if (choice_from_msg == NULLEVENT) {
							break;
						}
						else {
							msg_from_file.option = choice_from_msg;
							msg_from_file.event_msg = SETPOINTON;
							int data_temp = 0;
							while (TRUE) {
								fscanf_s(fin, "%d", &data_temp);
								if (data_temp == EVENTEND) {
									break;
								}
								msg_from_file.pos.push(data_temp);
							}
							MainRecord.RespondEvent(msg_from_file);
						}
					}
				}
				fclose(fin);
				//InvalidateRect(hDlg, nullptr, TRUE);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
//void DrawLine(HWND hWnd) {

	//HDC hdc = GetDC(hWnd);
	//MoveToEx(hdc, 10, 10, nullptr);
	//LineTo(hdc, 20, 20);
	//ReleaseDC(hWnd,hdc);
//}
INT_PTR CALLBACK Save(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	HWND hStaticText;
	queue<int> tempQ;
	switch (message)
	{
	case WM_INITDIALOG:
		hStaticText = GetDlgItem(hDlg, IDC_STATIC);
		SetWindowText(hStaticText, TEXT("在下方对话框输入文件路径以读取文件"));
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			if (LOWORD(wParam) == IDOK) {
				GetDlgItemText(hDlg, IDC_EDIT1, wrFilePath, MAX_PATHLENGTH);
				//InvalidateRect(hDlg, nullptr, TRUE);
				FILE* fout;
				_bstr_t b(wrFilePath);//wchar使用此宏转换
				char* file_path;
				file_path = b;
				fopen_s(&fout, file_path, "wt+");
				for (int index = 0; index < MainRecord.vec.size(); index++) {
					tempQ = MainRecord.vec[index]->OutObjPos();
					while (!tempQ.empty()) {
						fprintf_s(fout, "%d ", tempQ.front());
						//fscanf_s(fout, "%d", &tempQ.front());
						tempQ.pop();
					}
				}
				int data_end = DATAEND;
				fprintf_s(fout, "%d",data_end);
				fclose(fout);
			}
			
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}