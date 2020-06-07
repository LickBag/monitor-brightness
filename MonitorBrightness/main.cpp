#include "Function.h"
#include "resource.h"

constexpr auto WINDOW_WIDTH  = 366;
constexpr auto WINDOW_HEIGHT = 90;

int APIENTRY wWinMain(_In_ HINSTANCE     hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR        lpCmdLine,
                      _In_ int           nCmdShow)
{
	POINT ptWindow;
	ptWindow.x = (GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2;
	ptWindow.y = (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2;

    // ×¢²á´°¿ÚÀà
    WNDCLASS wc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WinProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = CLS_NAME;
    RegisterClass(&wc);

    HWND hWnd = CreateWindow(CLS_NAME, WIN_TITLE, WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX,
		ptWindow.x, ptWindow.y, WINDOW_WIDTH, 90, nullptr, nullptr, hInstance, nullptr);

    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
    RemoveMenu(hMenu, SC_RESTORE, MF_BYCOMMAND);
    RemoveMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    RemoveMenu(hMenu, SC_SIZE, MF_BYCOMMAND);
    RemoveMenu(hMenu, SC_SEPARATOR, MF_BYCOMMAND);

    SetProcessDPIAware();
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}