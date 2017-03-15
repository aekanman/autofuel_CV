#include"arduinoComm.h"
#include <cmath>
#include "stdafx.h"

using namespace std;

serial comm; //serial is a class type defined in these files, used for referring to the communication device
unsigned char command_set_buffer[10];
char message[10];

enum CommandSet //enum that will be used to get proper
{
	START_COMMAND,
	START_BYTE,
	END_BYTE,
	POSITION_COMMAND,
	ANGLE_COMMAND

};

void sendData(std::pair<int, int> target) {
	char buffer[10]; //= new char[10];
	int size = GeneratePositionMessage(2, -2, -1, buffer);
	comm.send_array(buffer, size); //The data is sent through the port
}

void InitializeCommandSet()
{
	//initialize the command set buffer. These bytes will be used in the messages sent to the arduino
	command_set_buffer[(int)START_COMMAND] = 0xAF;  //
	command_set_buffer[(int)START_BYTE] = 0xAA;
	command_set_buffer[(int)END_BYTE] = 0xFF;
	command_set_buffer[(int)POSITION_COMMAND] = 0x0A;
	command_set_buffer[(int)ANGLE_COMMAND] = 0x0B;
}


// Generates an array of bytes in the specified form with position data. The inputs are integers, but they will be 
//converted to bytes, so it is best to send values that are 0 - 255.
int GeneratePositionMessage(INT16 x, INT16 y, INT16 z, char buffer[10]) //out?
{
	//buffer = new char[10]; 												// total length of position message should be 10

																		/*

																		The messages should be in this form:
																		[START_BYTE][LENGTH OF DATA][TYPE OF COMMAND][DATA][END_BYTE]

																		The [data] part will consist of:
																		[[sign of x][value of x][sign of y][value of y][sign of z][value of z]]
																		*/



	buffer[0] = command_set_buffer[(int)START_BYTE];					// expected first byte for each message
	buffer[1] = 6;														// length of useful data following the ommand type
	buffer[2] = command_set_buffer[(int)POSITION_COMMAND];				// command type (eventually this will differentiate between position and angle commands)
	buffer[3] = (char)((x >> 8 & 0xFF));
	buffer[4] = (char)(x & 0xFF);
	buffer[5] = (char)((y >> 8 & 0xFF));
	buffer[6] = (char)(y & 0xFF);
	buffer[7] = (char)((z >> 8 & 0xFF));
	buffer[8] = (char)(z & 0xFF);
	buffer[9] = command_set_buffer[(int)END_BYTE];						//the expected end byte that will help determine when message is over.
	return 10;
}

//Just a psuedo main function showing how to use these functions
void initArduinoComm()
{
	InitializeCommandSet(); // call at beginning of program to fill array. (I guess we can hardcode the array too :P)
	comm.startDevice("COM4", 9600);
	comm.send_data(command_set_buffer[(int)START_COMMAND]);
}

void stopComm() {
	comm.stopDevice(); //The device is closed down
	_getch();
}
