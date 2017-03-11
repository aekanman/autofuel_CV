#pragma once
#ifndef APPCOMMANDS_H   
#define APPCOMMANDS_H

#include <tchar.h>
#include <windows.h>
#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")
#include <iostream>
#include <fstream>
#include <string>

bool getTextFromWeb();
bool txtFromFileToBool();
bool toBool(std::string const& s);
#endif