#pragma once

#include <Windows.h>

#include <ShellScalingApi.h>
#pragma comment(lib, "shcore.lib")

#include <CommCtrl.h>
#pragma comment(lib,"comctl32.lib")

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define CLS_NAME     L"MonitorBrightnessApp"        // 类名
#define WIN_TITLE    L"MonitorBrightness"        // 窗口标题
