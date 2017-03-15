
#include "hough.h"
#include "stdafx.h"

using namespace cv;
using namespace std;
Mat source;
vector<pair<int, int>> magnetTarget;
pair<double, double> distInCm;

Mat houghForever();

/** @function main */
pair<double, double> magnetTargetCoord()
{
	Mat src_gray;

	/// Read the image
	source = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/src.jpg", 1);
	//source = houghForever();

	if (!source.data)
	{
		return (pair<int, int>(-1, -1));
	}

	/// Convert it to gray
	cvtColor(source, src_gray, CV_BGR2GRAY);

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 20, 250, 0);

	Point targetPoints, center;
	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		bool getBiggerCircle = 0;
		if (i == 0) {
			getBiggerCircle = 1;
		}
		else {
			getBiggerCircle = int(cvRound(circles[i][2])) > int(cvRound(circles[i - 1][2])) ? 1 : 0;
		}
		if (getBiggerCircle) {
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
			int radius = cvRound(circles[i][2]);
			// circle center
			circle(source, center, 3, Scalar(0, 255, 0), -1, 8, 0);
			// circle outline
			circle(source, center, radius, Scalar(0, 0, 255), 3, 8, 0);
			// circle target
			targetPoints.x = center.x - radius * 0.6;//center 552, target 352
			targetPoints.y = center.y - radius * 0.3;//center 488, target 388
			circle(source, targetPoints, 20, Scalar(0, 215, 255), 3, 8, 0);

			//center of the frame 640,480
			//distance from center: targetx - 640 , targety-480
			//distance in cm: 0.025cm*(targetx - 640) , 0.025cm*(targety - 480)
			distInCm.first = 0.025 * (targetPoints.x - 640);
			distInCm.second = 0.025 * (targetPoints.y - 480);
		}
	}

	/// Show your results
	//namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	//imshow("Hough Circle Transform Demo", source);

	//return (pair<int, int>(-1,-1)); //test
	//waitKey(0);
	return pair<int, int>(distInCm.first, distInCm.second);
}

Mat captureImage() {
	VideoCapture cap(1); // open the default camera
	Mat frame;

	//captureVideoLegacy();

	if (!cap.isOpened())  // check if we succeeded
		return frame;

	cap >> frame; // get a new frame from camera
	
	return frame;
}

//runs hough circle continuously 
Mat houghForever() {
	VideoCapture cap(1); // open the default camera
	Mat frame;

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);

	//captureVideoLegacy();

	if (!cap.isOpened())  // check if we succeeded
		return frame;

	//cap >> frame; // get a new frame from camera
	while (1)
	{
		cap >> frame;
		// show live and wait for a key with timeout long enough to show images
		
		if (waitKey(30) <= 0)
			break;
		Mat src_gray;
		if (!frame.data)
		{
			break;
		}

		/// Convert it to gray
		cvtColor(frame, src_gray, CV_BGR2GRAY);

		/// Reduce the noise so we avoid false circle detection
		GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

		vector<Vec3f> circles;

		/// Apply the Hough Transform to find the circles
		HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 20, 250, 0);

		Point targetPoints, center;
		/// Draw the circles detected
		for (size_t i = 0; i < circles.size(); i++)
		{
			bool getBiggerCircle = 0;
			if (i == 0) {
				getBiggerCircle = 1;
			}
			else {
				getBiggerCircle = int(cvRound(circles[i][2])) > int(cvRound(circles[i - 1][2])) ? 1 : 0;
			}
			if (getBiggerCircle) {
				Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				// circle center
				circle(frame, center, 3, Scalar(0, 255, 0), -1, 8, 0);
				// circle outline
				circle(frame, center, radius, Scalar(0, 0, 255), 3, 8, 0);
				// circle target
				targetPoints.x = center.x - radius * 0.6;
				targetPoints.y = center.y - radius * 0.3;
				circle(frame, targetPoints, 20, Scalar(0, 215, 255), 3, 8, 0);
			}
		}
		imshow("Live", frame);
	}

	return frame;
}