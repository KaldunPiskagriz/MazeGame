#include "Logger.hpp"

Logger::Logger() {
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hConsole, &info);
	info.ColorTable[1] = RGB(255, 255, 255);
	info.ColorTable[2] = RGB(255, 255, 0);
	info.ColorTable[3] = RGB(255, 0, 0);
	info.ColorTable[4] = RGB(50, 50, 255);
	SetConsoleScreenBufferInfoEx(hConsole, &info);
}

void Logger::PrintMessage(const std::string& message)	{
	std::lock_guard guard(mutex);
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << "[ EnigneLogger ][ info ]: " << message << '\n';
}


void Logger::PrintImportantMessage(const std::string& message) {
	std::lock_guard guard(mutex);
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << "[ EnigneLogger ][ ";
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << "important";
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << " ]: " << message << '\n';
}


void Logger::PrintWarn(const std::string& message) {
	std::lock_guard guard(mutex);
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << "[ EnigneLogger ][ ";
	SetConsoleTextAttribute(hConsole, 2);
	std::cout << "warn";
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << " ]: " << message << '\n';
}

void Logger::PrintError(const std::string& message) {
	std::lock_guard guard(mutex);
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << "[ EnigneLogger ][ ";
	SetConsoleTextAttribute(hConsole, 3);
	std::cout << "ERROR";
	SetConsoleTextAttribute(hConsole, 1);
	std::cout << " ]: " << message << '\n';
}