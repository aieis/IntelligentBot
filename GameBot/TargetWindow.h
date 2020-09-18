#pragma once
#ifndef TARGETWINDOW_H_
#define TARGETWINDOW_H_

#include <opencv2/core.hpp>
#include <Windows.h>

class TargetWindow
{
public:
	int w, h;
	HWND hWnd;
	TargetWindow(std::string name);
    bool PopulateMaterial(cv::Mat& aMaterial);
};


#endif
