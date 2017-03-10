/**
* @function moments_demo.cpp
* @brief Demo code to calculate moments
* @author OpenCV team
*/

#include "cheese.h"
#include "hough.h"

using namespace cv;
using namespace std;

pair<int, int> magnetTarget;
enum States {Idle,DetectDoor,OpenDoor,RemoveCap,InsertNozzle,RemoveNozzle};
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

	//get url data
	//check url data
	Mat photo;
	while (1) {
		switch (state)
		{
		case Idle:
			
			state = DetectDoor;
			break;
		case DetectDoor:
			magnetTarget = magnetTargetCoord();
			
			if (magnetTarget.first == -1 && magnetTarget.second == -1)
				break;

			state = OpenDoor;
			break;
		case OpenDoor:
			photo = takePhotoAndMask();
			state = RemoveCap;
			break;
		case RemoveCap:
			
			state = InsertNozzle;
			break;
		}
		//break;
	}
}
