#include "cheese.h"
#include "hough.h"

using namespace cv;
using namespace std;


float innerAngle(float px1, float py1, float px2, float py2, float cx1, float cy1);
float getAngle(double x1, double x2, double y1, double y2);

/**
* @function main
*/
bool takePhotoAndMask()
{
	///// Load source image
	Mat src1 = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/realyellow1red.jpg", IMREAD_COLOR);
	//Mat src1 = captureImage();

	Mat maskYellow, maskRed;
	//paint 
	//cv::Scalar lowerb = cv::Scalar(0, 235, 235);
	//cv::Scalar upperb = cv::Scalar(30, 255, 255);
	//envelope
	cv::Scalar lowerb = cv::Scalar(0, 160, 220);
	cv::Scalar upperb = cv::Scalar(80, 255, 255);
	cv::inRange(src1, lowerb, upperb, maskYellow);
	imwrite("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/maskedAndSavedYellow.jpg", maskYellow);

	cv::Scalar lowerRed = cv::Scalar(0,0, 50);
	cv::Scalar upperRed = cv::Scalar(20, 20, 255);
	cv::inRange(src1,lowerRed, upperRed, maskRed);
	imwrite("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/maskedAndSavedRed.jpg", maskRed);

	if (countNonZero(maskYellow) < 1 || countNonZero(maskRed) < 1)
		return 0; //return 0 if there's no yellow/red tape
	
	return 1;
}

/** @function findAngle
the angle between fuel cap dots*/
int findAngle()
{
	Mat src_gray;

	//CURL* curl;
	//CURLcode result;

	//curl = curl_easy_init();
	//curl_easy_setopt(curl, CURLOPT_URL, "www.atakanefekanman.com/bool.txt");

	//result = curl_easy_perform(curl);

	//curl_easy_cleanup(curl);

	Mat src = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/maskedAndSavedYellow.jpg", IMREAD_COLOR);

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
	vector<pair<int, int>> center_points;

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		center_points.push_back(pair<int, int>(circles[i][0], circles[i][1]));
	}

	line(src, Point(center_points.at(0).first, center_points.at(0).second), Point(center_points.at(1).first, center_points.at(1).second), Scalar(0, 0, 255), 3);
	int angle = 0;

	//compare ys
	//lower y is 0p
	//p0 is cntr
	//p3 is x0 y1
	//if x1<x0 ccw
	//if (center_points.at(0).second > center_points.at(1).second && center_points.at(0).first > center_points.at(1).first) {
		//angle = int(innerAngle(center_points.at(1).first, center_points.at(0).second, center_points.at(1).first, center_points.at(1).second, center_points.at(0).first, center_points.at(0).second));
	//}
	//else if (center_points.at(0).second > center_points.at(1).second && center_points.at(0).first < center_points.at(1).first) {
		//angle = int(getAngle(center_points.at(0).first, center_points.at(1).second, center_points.at(1).first, center_points.at(1).second, center_points.at(0).first, center_points.at(0).second));
	//}
	angle = int(getAngle(center_points.at(0).first, center_points.at(0).second, center_points.at(1).first, center_points.at(1).second));
		

	//angle = int(innerAngle(center_points.at(1).first, center_points.at(0).second, center_points.at(1).first, center_points.at(1).second, center_points.at(0).first, center_points.at(0).second));


	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);

	return angle;
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

	float getAngle(double x1, double y1, double x2, double y2)
	{
		pair<double, double> p1, p2;

		if (y1 == y2)
		{
			return 0;
		}
		if (x1 == x2)
		{
			return 90;
		}
		if (y1 < y2)
		{
			p1.first = x1;
			p1.second = y1;
			p2.first = x2;
			p2.second = y2;
		}
		else
		{
			p1.first = x2;
			p1.second = y2;
			p2.first = x1;
			p2.second = y1;
		}

		bool ccw = (p2.first < p1.first);

		double adj = p2.second - p1.second;
		double x_dist = (p2.first - p1.first);
		double y_dist = (p2.second - p1.second);
		double hyp = sqrt((x_dist * x_dist) + (y_dist * y_dist));

		double angle = acos(adj / hyp);
		angle *= (180 / 3.14159265359);

		if (!ccw)
			return -angle;
		return angle;
	}

	pair<double, double> findGripperCenter()
	{
		Mat src_gray;

		//CURL* curl;
		//CURLcode result;

		//curl = curl_easy_init();
		//curl_easy_setopt(curl, CURLOPT_URL, "www.atakanefekanman.com/bool.txt");

		//result = curl_easy_perform(curl);

		//curl_easy_cleanup(curl);

		Mat src = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/maskedAndSavedRed.jpg", IMREAD_COLOR);

		if (!src.data)
		{
			return (pair<int, int>(-1, -1));
		}

		/// Convert it to gray
		cvtColor(src, src_gray, CV_BGR2GRAY);

		/// Reduce the noise so we avoid false circle detection
		GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

		vector<Vec3f> circles;

		/// Apply the Hough Transform to find the circles
		HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 20, 0, 0);
		pair<int, int> center_point;

		/// Draw the circles detected
		for (size_t i = 0; i < circles.size(); i++)
		{
			center_point.first = circles[i][0];
			center_point.second = circles[i][1];
		}


		/// Show your results
		namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
		imshow("Hough Circle Transform Demo", src);

		return center_point;
	}