
#include "hough.h"

using namespace cv;
using namespace std;
Mat source;
vector<pair<int, int>> magnetTarget;
int captureVideoLegacy();

/** @function main */
pair<int, int> magnetTargetCoord()
{
	Mat src_gray;

	/// Read the image
	source = imread("C:/Users/Ben/Documents/Visual Studio 2015/Projects/autofuel_CV/img/src.jpg", 1);
	//source = captureImage();

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
			targetPoints.x = center.x - radius * 0.6;
			targetPoints.y = center.y - radius * 0.55;
			circle(source, targetPoints, 20, Scalar(0, 215, 255), 3, 8, 0);
		}
	}

	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", source);

	//return (pair<int, int>(-1,-1)); //test
	waitKey(0);
	return (pair<int, int>(targetPoints.x, targetPoints.y));
}

Mat captureImage() {
	VideoCapture cap(-1); // open the default camera
	Mat frame;

	captureVideoLegacy();

	if (!cap.isOpened())  // check if we succeeded
		return frame;


	for (;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
					  // do any processing
		//imwrite("image.png", frame);
		imshow("image.png", frame);
		if (waitKey(30) >= 0) break;   // you can increase delay to 2 seconds here
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return frame;
}

int captureVideoLegacy()
{
	VideoCapture cap(0);
	Mat frame;
	if(!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	cvNamedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	//cvNamedWindow("Drawing Control", CV_WINDOW_AUTOSIZE);

	while (true)
	{
		bool bSuccess = cap.read(frame);
		imshow("Control",frame);
	}
}