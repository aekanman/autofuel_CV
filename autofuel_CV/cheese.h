#pragma once
#ifndef CHEESE_H   
#define CHEESE_H

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

bool takePhotoAndMask();
int findAngle();
#endif