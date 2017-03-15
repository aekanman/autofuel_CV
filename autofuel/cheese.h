#ifndef CHEESE_H   
#define CHEESE_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;

bool takePhotoAndMask();
int findAngle();
pair<double, double> findGripperCenter();
#endif