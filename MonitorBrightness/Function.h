#pragma once
#include"app.h"

LRESULT _stdcall WinProc(HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam);

BOOL GetMonitorBrightness(DWORD& dCur, DWORD& dMin, DWORD& dMax);

BOOL SetMonitorBrightness(DWORD dwCurBright);