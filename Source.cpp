#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment (lib, "comctl32")

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hToolBar;
	switch (msg)
	{
	case WM_CREATE:
		{
			InitCommonControls();
			TBBUTTON ToolbarButtons[] = {
				{ 0, ID_COMMAND1, TBSTATE_ENABLED, BTNS_BUTTON, { 0 }, 0, 0 },
				{ 1, ID_COMMAND2, TBSTATE_ENABLED, BTNS_BUTTON, { 0 }, 0, 0 },
				{ 2, ID_COMMAND3, TBSTATE_ENABLED, BTNS_BUTTON, { 0 }, 0, 0 },
				{ 3, ID_COMMAND4, TBSTATE_ENABLED, BTNS_BUTTON, { 0 }, 0, 0 },
				{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, { 0 }, 0, 0 }
			};
			hToolBar = CreateToolbarEx(hWnd, WS_CHILD | WS_VISIBLE | TBSTYLE_FLAT, ID_TOOLBAR, 4, GetModuleHandle(0), IDR_TOOLBAR1, ToolbarButtons, _countof(ToolbarButtons) - 1 /* セパレータの分を除く */, 0, 0, 0, 0, sizeof(TBBUTTON));
			SendMessage(hToolBar, TB_INSERTBUTTON, 2, (LPARAM)&ToolbarButtons[_countof(ToolbarButtons) - 1]); // セパレータを挿入
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COMMAND1:
			MessageBox(hWnd, TEXT("1"), 0, 0);
			break;
		case ID_COMMAND2:
			MessageBox(hWnd, TEXT("2"), 0, 0);
			break;
		case ID_COMMAND3:
			MessageBox(hWnd, TEXT("3"), 0, 0);
			break;
		case ID_COMMAND4:
			MessageBox(hWnd, TEXT("4"), 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Toolbar"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
