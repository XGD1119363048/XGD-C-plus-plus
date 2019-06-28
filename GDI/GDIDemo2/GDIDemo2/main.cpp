#include <Windows.h>
#include <tchar.h>
#include <time.h>

#pragma comment(lib, "winmm.lib")

#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 800
#define WINDOW_TITLE L"GDI程序核心框架"

HDC g_hdc = NULL;//设备环境句柄
HPEN g_hPen[7] = { 0 };//画笔句柄数组
HBRUSH g_hBrush[7] = { 0 };//画刷句柄数组
//画笔样式
int g_iPenStyle[7] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME };
//画刷样式
int g_iBrushStyle[6] = { HS_VERTICAL, HS_HORIZONTAL, HS_CROSS, HS_DIAGCROSS, HS_FDIAGONAL, HS_BDIAGONAL };

//窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

//资源初始化
BOOL Game_Init(HWND hwnd);

//绘图代码
VOID Game_Paint(HWND hwnd);

//资源清理
BOOL Game_CleanUp(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//设计窗口
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_VREDRAW | CS_HREDRAW;
	wndClass.lpfnWndProc = WindowProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = (HICON)::LoadImage(NULL, _T("Girl.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = _T("ForTheDreamOfGameDevelop");

	//注册窗口
	if (!RegisterClassEx(&wndClass))
	{
		return -1;
	}

	//创建窗口
	HWND hwnd = CreateWindow(L"ForTheDreamOfGameDevelop", WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	//调整窗口位置
	MoveWindow(hwnd, 200, 50, WINDOW_WIDTH, WINDOW_HEIGHT, true);

	//显示窗口
	ShowWindow(hwnd, nCmdShow);

	//窗口更新
	UpdateWindow(hwnd);

	//游戏资源初始化
	if (!Game_Init(hwnd))
	{
		MessageBox(hwnd, L"资源初始化失败", L"消息窗口", 0);
		return FALSE;
	}
	/*PlaySound(L"【9i5i.com】夏影 - 麻枝准.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);*/

	//消息循环
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	//窗口类的注销
	UnregisterClass(L"ForTheDreamOfGameDevelop", wndClass.hInstance);

	return 0;
}

//窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT paintStruct;

	switch (message)
	{
		case WM_PAINT:
		{
			g_hdc = BeginPaint(hwnd, &paintStruct);
			Game_Paint(hwnd);
			EndPaint(hwnd, &paintStruct);
			ValidateRect(hwnd, NULL);
			break;
		}
		case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE)
			{
				DestroyWindow(hwnd);
			}
			break;
		}
		case WM_DESTROY:
		{
			Game_CleanUp(hwnd);
			PostQuitMessage(0);
			break;
		}
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

//简单初始化
BOOL Game_Init(HWND hwnd)
{
	g_hdc = GetDC(hwnd);

	/*srand((unsigned)time(NULL));
	for (int i = 0; i <= 6; i++)
	{
		g_hPen[i] = CreatePen(g_iPenStyle[i], 1, RGB(rand() % 256, rand() % 256, rand() % 256));
		if (i == 6)
			g_hBrush[i] = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		else
			g_hBrush[i] = CreateHatchBrush(g_iBrushStyle[i], RGB(rand() % 256, rand() % 256, rand() % 256));
	}
*/
	Game_Paint(hwnd);
	ReleaseDC(hwnd, g_hdc);
	return TRUE;
}

//在次函数中进行绘制操作
VOID Game_Paint(HWND hwnd)
{
	HFONT hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, L"微软雅黑");
	SelectObject(g_hdc, hFont);
	SetBkMode(g_hdc, TRANSPARENT);

	wchar_t text1[] = L"我们所有的梦想都可以成真，只要我们有勇气去追求它们";
	wchar_t text2[] = L"All our dream can come true, if we have the courage to pursue them.";
	wchar_t text3[] = L"--------沃尔特 迪斯尼";

	SetTextColor(g_hdc, RGB(50, 255, 50));
	TextOut(g_hdc, 30, 150, text1, wcslen(text1));

	SetTextColor(g_hdc, RGB(50, 50, 255));
	TextOut(g_hdc, 30, 200, text2, wcslen(text2));

	SetTextColor(g_hdc, RGB(255, 50, 50));
	TextOut(g_hdc, 500, 250, text3, wcslen(text3));
	DeleteObject(hFont);

}

//资源清理函数
BOOL Game_CleanUp(HWND hwnd)
{
	/*for (int i = 0; i <= 6; i++)
	{
		DeleteObject(g_hPen[i]);
		DeleteObject(g_hBrush[i]);
	}*/
	return TRUE;
}