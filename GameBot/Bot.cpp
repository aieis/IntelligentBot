#include <iostream>
#include <Windows.h>

#include "TargetWindow.h"
#include "ObjectFinder.h"
#include "utils.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

void click(HWND hwnd, cv::Point cvp);

int main(int argc, char** argv)
{
    TargetWindow window(argv[1]);
    ObjectFinder aFinder(argv[2]);

    cv::Mat mat;
    window.PopulateMaterial(mat);

    cv::cvtColor(mat, mat, cv::COLOR_BGRA2BGR);

    std::cout << type2str(mat.type()) << "\n";

    cv::imshow("Img", mat);
    cv::waitKey(0);

    cv::Point click_loc = aFinder.find(mat);

    click(window.hWnd, click_loc);

    window.PopulateMaterial(mat);
    cv::imshow("Img", mat);
    cv::waitKey(0);

}

void click(HWND hwnd, cv::Point cvp)
{
    POINT p;
    p.x = cvp.x;
    p.y = cvp.y;

    LPARAM lparam = MAKELONG(p.x, p.y);
	SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lparam);
	SendMessage(hwnd, WM_LBUTTONUP, 0, lparam);

}
