#pragma once
#include <stdio.h>
#include "conio.h"
#include <iostream>
#include <windows.h>
#include <string>
#include "Singleton.hpp"
#include <mutex>

class Logger : public Singleton<Logger>{

	std::recursive_mutex mutex;
	CONSOLE_SCREEN_BUFFER_INFOEX info;
	HANDLE hConsole;
	
public:

	Logger();
	void PrintMessage(const std::string& message);
	void PrintImportantMessage(const std::string& message);
	void PrintWarn(const std::string& message);
	void PrintError(const std::string& message);

};