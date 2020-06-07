#include "Function.h"
#include "highlevelmonitorconfigurationapi.h"

#pragma comment(lib, "Dxva2.lib")

BOOL GetMonitorBrightness(DWORD& dCur, DWORD& dMin, DWORD& dMax)
{
    BOOL bRet = FALSE;
    LPPHYSICAL_MONITOR pAryPhysicalMonitor = nullptr;

    HMONITOR hMonitor = MonitorFromWindow(HWND_DESKTOP, MONITOR_DEFAULTTOPRIMARY);
    if (hMonitor)
    {
        do
        {
            DWORD dwPhysicalMonitors = 0;
            bRet = GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &dwPhysicalMonitors);
            if (!bRet) { break; }

            LPPHYSICAL_MONITOR pAryPhysicalMonitor = (LPPHYSICAL_MONITOR)malloc(dwPhysicalMonitors * sizeof(PHYSICAL_MONITOR));
            ZeroMemory(pAryPhysicalMonitor, sizeof(PHYSICAL_MONITOR) * dwPhysicalMonitors);
            bRet = GetPhysicalMonitorsFromHMONITOR(hMonitor, dwPhysicalMonitors, (LPPHYSICAL_MONITOR)pAryPhysicalMonitor);
            if (!bRet) { break; }

            bRet = GetMonitorBrightness(((LPPHYSICAL_MONITOR)pAryPhysicalMonitor)[0].hPhysicalMonitor, &dMin, &dCur, &dMax);
            DestroyPhysicalMonitors(dwPhysicalMonitors, pAryPhysicalMonitor);
            if (!bRet) { break; }

            bRet = TRUE;

        } while (false);

        if (pAryPhysicalMonitor)
        {
            free(pAryPhysicalMonitor);
            pAryPhysicalMonitor = nullptr;
        }
    }

    return bRet;
}


BOOL SetMonitorBrightness(DWORD dwCurBright)
{
    BOOL bRet = FALSE;

    HMONITOR hMonitor = MonitorFromWindow(HWND_DESKTOP, MONITOR_DEFAULTTOPRIMARY); 
    if (hMonitor)
    {
        do
        {
            DWORD dwPhysicalMonitors = 0;
            bRet = GetNumberOfPhysicalMonitorsFromHMONITOR(hMonitor, &dwPhysicalMonitors);
            if (!bRet) { break; }

            LPPHYSICAL_MONITOR pAryPhysicalMonitor = (LPPHYSICAL_MONITOR)malloc(dwPhysicalMonitors * sizeof(PHYSICAL_MONITOR));
            ZeroMemory(pAryPhysicalMonitor, sizeof(PHYSICAL_MONITOR) * dwPhysicalMonitors);
            bRet = GetPhysicalMonitorsFromHMONITOR(hMonitor, dwPhysicalMonitors, (LPPHYSICAL_MONITOR)pAryPhysicalMonitor);
            if (!bRet) { break; }

            BOOL bRet = SetMonitorBrightness(((LPPHYSICAL_MONITOR)pAryPhysicalMonitor)[0].hPhysicalMonitor, dwCurBright);
            if (!bRet) { break; }

        } while (false);
    }

    return bRet;
}
