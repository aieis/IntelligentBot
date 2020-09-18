#include "ObjectFinder.h"

#include "utils.h"

#include <string>
#include <vector>
#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


ObjectFinder::ObjectFinder(std::string path)
{
	object = cv::imread(path);
	w = object.size[1];
	h = object.size[0];
}


cv::Point ObjectFinder::find(cv::Mat window)
{
	cv::Mat result;

	int rcols = window.cols - object.cols + 1;
	int rrows = window.rows - object.rows + 1;

	result.create(rrows, rcols, CV_8UC4);

	std::cout << type2str(object.type()) << "\n";

	int match_method = cv::TM_SQDIFF;
	cv::matchTemplate(window, object, result, match_method);
	cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

	double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;

	cv::Point matchLoc;
	cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

	matchLoc = match_method == cv::TM_SQDIFF ? minLoc : maxLoc;

	/*
	cv::Mat templ = object;

	//cv::rectangle(window, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), cv::Scalar::all(0), 2, 8, 0);
	cv::drawMarker(result, cv::Point(matchLoc.x, matchLoc.y), cv::Scalar::all(0), cv::MARKER_CROSS, 40, 2);

	//cv::imshow("One", window);

	
	cv::imshow("Two", result);
	cv::waitKey(0);
	*/

	return matchLoc;
}

