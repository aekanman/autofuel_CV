#pragma once
#ifndef ARDUINOCOMM_H   
#define ARDUINOCOMM_H

#include <stdio.h>
#include <iostream>
#include <conio.h>
#include "tserial.h"
#include "bot_control.h"

using namespace std;
void sendData(std::pair<int, int> target);
void initArduinoComm();
void stopComm();
int GeneratePositionMessage(int x, int y, int z, char buffer[]);
#endif