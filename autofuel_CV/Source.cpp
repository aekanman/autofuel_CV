/**
* @function moments_demo.cpp
* @brief Demo code to calculate moments
* @author OpenCV team
*/

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

/**
* @function main
*/
int si(int, char** argv)
{
	///// Load source image

	//Mat1b src1 = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/test2/2.jpg", IMREAD_GRAYSCALE);
	////src1 x=[0 1280], y=[0 960]

	//Moments mu = moments(src1, false);
	//Point center;
	////get center
	//center.x = mu.m10 / mu.m00;
	//center.y = mu.m01 / mu.m00;

	//center.x -= 260;
	//center.y -= 200;

	//printf(" * X[%d] - Y[%d] \n", center.x, center.y);

	//Mat3b res;
	//cvtColor(src1, res, CV_GRAY2BGR);
	//circle(res, center, 15, Scalar(0, 0, 255));
	//imshow("Result", res);

	//waitKey(0);
	return(0);


}
