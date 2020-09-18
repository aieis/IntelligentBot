#pragma once
#ifndef OBJECTFINDER_H_
#define OBJECTFINDER_H_

#include <opencv2/core/core.hpp>
#include <string>

class ObjectFinder {
public:
	cv::Mat object;
	int w;
	int h;

	ObjectFinder(std::string path);
	cv::Point find(cv::Mat window);
};

#endif

