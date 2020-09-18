#include <string>
#include <Windows.h>
#include "TargetWindow.h"

#include <opencv2/core.hpp>

TargetWindow::TargetWindow(std::string name)
{
	std::wstring wstr = std::wstring(name.begin(), name.end());
	LPCWSTR window_name = wstr.c_str();
	hWnd = FindWindow(NULL, window_name);

	RECT window_rect;
	GetWindowRect(hWnd, &window_rect);

	w = window_rect.right - window_rect.left;
	h = window_rect.bottom - window_rect.top;
}

bool TargetWindow::PopulateMaterial(cv::Mat & aMaterial)
{
    HDC hdcWindow = GetDC(hWnd);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hdcWindow);
    if (!hwindowCompatibleDC)
    {
        return false;
    }

    if (!SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR))
    {
        DeleteDC(hwindowCompatibleDC);
        return false;
    }

    HBITMAP hbwindow = CreateCompatibleBitmap(hdcWindow, w, h);
    if (!hbwindow)
    {
        DeleteDC(hwindowCompatibleDC);
        return false;
    }

    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = w;
    bi.biHeight = -h;
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    if (!SelectObject(hwindowCompatibleDC, hbwindow))
    {
        DeleteObject(hbwindow);
        DeleteDC(hwindowCompatibleDC);
        return false;
    }

    if (!StretchBlt( hwindowCompatibleDC, 0, 0,
        w, h,
        hdcWindow,
        0, 0,
        w, h,
        SRCCOPY))
    {
        DeleteObject(hbwindow);
        DeleteDC(hwindowCompatibleDC);
        return false;
    }

    aMaterial.release();
    aMaterial.create(h, w, CV_8UC4);

    if (!GetDIBits(
        hdcWindow,
        hbwindow,
        0,
        h,
        aMaterial.data,
        (BITMAPINFO*)&bi,
        DIB_RGB_COLORS))
    {
        aMaterial.release();
        DeleteObject(hbwindow);
        DeleteDC(hwindowCompatibleDC);
        return false;
    }

    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);

    const bool success = aMaterial.cols > 0 && aMaterial.rows > 0;
    if (!success)
    {
        aMaterial.release();
    }

    return success;
}

