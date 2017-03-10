#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
//#include "curl/curl.h"

using namespace cv;
using namespace std;

float innerAngle(float px1, float py1, float px2, float py2, float cx1, float cy1);

/** @function main */
int main1(int argc, char** argv)
{
	Mat src, src_gray;

	//CURL* curl;
	//CURLcode result;

	//curl = curl_easy_init();
	//curl_easy_setopt(curl, CURLOPT_URL, "www.atakanefekanman.com/bool.txt");

	//result = curl_easy_perform(curl);

	//curl_easy_cleanup(curl);


	/// Read the image
	src = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/whitedotsr.jpg", 1);

	if (!src.data)
	{
		return -1;
	}

	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 20, 0, 0);
	vector<pair<int,int>> center_points;

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		center_points.push_back(pair<int, int>(circles[i][0], circles[i][1]));
	}

	line(src, Point(center_points.at(0).first, center_points.at(0).second), Point(center_points.at(1).first, center_points.at(1).second), Scalar(0,0,255), 3);

	//compare ys
	//lower y is 0p
	//p0 is cntr
	//p3 is x0 y1
	//if x1<x0 ccw
	if (center_points.at(0).second > center_points.at(1).second)
		center_points.at(0).swap(center_points.at(1));

	int angle = int(innerAngle(center_points.at(0).first + 40, center_points.at(0).second, center_points.at(1).first, center_points.at(1).second, center_points.at(0).first, center_points.at(1).second));
	int test = 5;
	char testchar = test & 0xFF;

	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);


	waitKey(0);
	return 0;
}

float innerAngle(float px1, float py1, float px2, float py2, float cx1, float cy1)
{

	float dist1 = sqrt((px1 - cx1)*(px1 - cx1) + (py1 - cy1)*(py1 - cy1));
	float dist2 = sqrt((px2 - cx1)*(px2 - cx1) + (py2 - cy1)*(py2 - cy1));

	float Ax, Ay;
	float Bx, By;
	float Cx, Cy;

	//find closest point to C
	//printf("dist = %lf %lf\n", dist1, dist2);

	Cx = cx1;
	Cy = cy1;
	if (dist1 < dist2)
	{
		Bx = px1;
		By = py1;
		Ax = px2;
		Ay = py2;


	}
	else {
		Bx = px2;
		By = py2;
		Ax = px1;
		Ay = py1;
	}


	float Q1 = Cx - Ax;
	float Q2 = Cy - Ay;
	float P1 = Bx - Ax;
	float P2 = By - Ay;


	float A = acos((P1*Q1 + P2*Q2) / (sqrt(P1*P1 + P2*P2) * sqrt(Q1*Q1 + Q2*Q2)));

	A = A * 180 / 3.14159265359;

	return A;
}