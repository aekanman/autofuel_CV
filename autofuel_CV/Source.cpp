/**
* @function moments_demo.cpp
* @brief Demo code to calculate moments
* @author OpenCV team
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "cheese.h"
#include "hough.h"
#include "appCommands.h"
#include "arduinoComm.h"

using namespace cv;
using namespace std;

pair<int, int> magnetTarget;
enum States {Idle,DetectDoor,OpenDoor,RemoveCap,InsertNozzle,RemoveNozzle, ErrorCase};
/**
0:idle/polling
1:detecting the center of the fuel door
2:openning the fuel door
3:removing the cap
4:inserting the nozzle
5:
/

/**
* @function main
*/
int main(int, char** argv)
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
			sendData();
			appChanged = getTextFromWeb();
			while (1) { 
				if (appChanged != getTextFromWeb())
					break;
			}
			 
			state = DetectDoor;
			break;
		case DetectDoor:
			prevState = DetectDoor;
			magnetTarget = magnetTargetCoord();

			if (magnetTarget.first == -1 && magnetTarget.second == -1)
				break;

			state = OpenDoor;
			break;
		case OpenDoor:
			prevState = OpenDoor;
			//command to initiate the magnet movement
			state = RemoveCap;
			break;
		case RemoveCap:
			prevState = RemoveCap;
			yellowDetected = takePhotoAndMask();
			angle = findAngle();
			state = InsertNozzle;
			//command to move the gripper
			break;
		case InsertNozzle:
			prevState = InsertNozzle;

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