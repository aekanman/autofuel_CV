// Project Autofuel's Computer Vision Software
// Author: Atakan Efe Kanman
// autofuel.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace cv;
using namespace std;

pair<double, double> magnetTarget;
pair<double, double> gripperCenter;

enum States { Idle, DetectDoor, OpenDoor, RemoveCap, InsertNozzle, RemoveNozzle, ErrorCase };
/**
0:idle/polling
1:detecting the center of the fuel door
2:openning the fuel door
3:removing the cap
4:inserting the nozzle
5:removing the nozzle and everything else
/**/

int main()
{
	States state = Idle;
	States prevState = ErrorCase;

	Mat photo;
	int angle = 0;
	bool appChanged = 0, yellowDetected = 0;
	while (1) {
		switch (state)
		{
		case Idle:
			prevState = Idle;
			
			appChanged = getTextFromWeb();
			while (1) {
			if (appChanged != getTextFromWeb())
				break;
			}

			state = DetectDoor;
			break;
		case DetectDoor:
			initArduinoComm();
			prevState = DetectDoor;
			magnetTarget = magnetTargetCoord();

			if (magnetTarget.first == -1 && magnetTarget.second == -1)
				break;

			state = OpenDoor;
			break;
		case OpenDoor:
			prevState = OpenDoor;
			command to initiate the magnet movement
			initArduinoComm();
			sendData(magnetTarget);

			state = RemoveCap;
			break;
		case RemoveCap:
			prevState = RemoveCap;
			yellowDetected = takePhotoAndMask();
			gripperCenter = findGripperCenter();
			//if (gripperCenter.first == -1 && gripperCenter.second == -1 || !yellowDetected)
				//break;
			//angle = findAngle();
			//sendData(pair<int, int>(50, 50));
			state = InsertNozzle;
			//command to move the gripper
			break;
		case InsertNozzle:
			prevState = InsertNozzle;
			//send command to insert the nozzle

			state = RemoveNozzle;
			break;
		case RemoveNozzle:
			prevState = RemoveNozzle;

			break;
		case ErrorCase:
			break;
		}

		//break;
	}
}

