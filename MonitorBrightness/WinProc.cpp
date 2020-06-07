#include "Function.h"

constexpr auto TRACKBAR_WIDTH = 30;  // 滑块宽度

HWND g_hTrackBar = nullptr;    // 滑块

HWND CreateTrack(HWND hWnd, HINSTANCE hInst)
{
    DWORD dwMin = 0, dwMax = 100, dwCur = 0;
    GetMonitorBrightness(dwCur, dwMin, dwMax);

    HWND hTrack = CreateWindowEx(0, TRACKBAR_CLASS, TEXT("Trackbar Control"),
        WS_CHILD | WS_VISIBLE 
        | TBS_HORZ  // 竖直的
        | TBS_BOTH  // 把手指两边
        | TBS_AUTOTICKS // 显示刻度
        | TBS_FIXEDLENGTH  // 处理 TBM_SETTHUMBLENGTH 消息
        | TBS_TOOLTIPS     // 显示当前的数值
        | TBS_DOWNISLEFT 
        , 0, 0, 350, 66, hWnd, nullptr, hInst, nullptr);

    SendMessage(hTrack, TBM_SETRANGE, (WPARAM)TRUE, (LPARAM)MAKELONG(dwMin, dwMax));  // 最小最大刻度
    SendMessage(hTrack, TBM_SETTHUMBLENGTH, TRACKBAR_WIDTH, 0); // 把手大小
    SendMessage(hTrack, TBM_SETTIPSIDE, TBTS_TOP, 0); // tooltip显示位置
    SendMessage(hTrack, TBM_SETPAGESIZE, 0, 1); // 鼠标点击的调整大小
    SendMessage(hTrack, TBM_SETPOS, TRUE, dwCur); // 当前位置0
    SendMessage(hTrack, TBM_SETTICFREQ, 10, 0); // 设置显示的刻度的频率, 每隔10个画一个刻度线

    return hTrack;
}


// 窗口函数
LRESULT _stdcall WinProc(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;
            g_hTrackBar = CreateTrack(hWnd, lpCreateStruct->hInstance);
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }

        // 处理滑条值变消息
        case WM_HSCROLL:
        {
            INT32 nCurBrightness = (BYTE)SendMessage(g_hTrackBar, TBM_GETPOS, 0, 0);
            SetMonitorBrightness((DWORD)nCurBrightness);
            break;
        }

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            break;
        }

        default:
        {
            return DefWindowProc(hWnd, msg, wParam, lParam);
        }
    }
    return 0;
}