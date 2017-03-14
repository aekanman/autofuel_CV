#pragma once
#pragma once
#ifndef HOUGH_H   
#define HOUGH_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

std::pair<double, double> magnetTargetCoord();
cv::Mat captureImage();

#endif