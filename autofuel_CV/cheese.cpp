#include "cheese.h"

using namespace cv;
using namespace std;

/**
* @function main
*/
Mat takePhotoAndMask()
{
	///// Load source image
	Mat src1 = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/yellowdotsr.jpg", IMREAD_COLOR);

	//imshow("source", src1);
	Mat mask;
	cv::Scalar lowerb = cv::Scalar(0, 235, 235);
	cv::Scalar upperb = cv::Scalar(30, 255, 255);
	cv::inRange(src1, lowerb, upperb, mask);

	imshow("mask", mask);

	waitKey(0);
	return(mask);
}
