#ifndef CORE_H
#define CORE_H

#if defined(_WIN32) || defined(_WIN64)
#   define Windows
#	include "windows.h"
#elif defined(__APPLE__)
#   define MacOS
#elif defined(__unix__) || defined(__unix)
#   define Linux
#	include <stdio.h>
#	include <sys/ioctl.h>
#else
#   error unsupported platform
#endif

#include <fstream>
#include <string>
#include "cereal/archives/json.hpp"
namespace core {

	namespace experimental { // Experimental stuff

		namespace console {


			int health{100};
			int attackModifier{1};
			int defenseModifier{1};
			bool godMode{false};

			void save() {
				std::string name{".variables"};

				std::ofstream os(("console/" + name + ".json"));
				cereal::JSONOutputArchive archive(os);

				archive( CEREAL_NVP(health),
				         CEREAL_NVP(attackModifier),
				         CEREAL_NVP(defenseModifier),
				         CEREAL_NVP(godMode) ); // Names the output the same as the variable name
			}
			/*void load() {
				std::ifstream is("console/" + name + ".json");
				cereal::JSONInputArchive archive(is);

				archive( name, age, gender );
			}*/
			void startConsole() {
#if defined(Windows)
				ShellExecute(NULL, "open", "console\\KrozConsole.exe", NULL, NULL, SW_SHOWDEFAULT);//Need this to close as parent closes, need to use SendMessage();
#elif defined(Linux)
#endif
			}
		};
	}
	
	// This is used to handle user input while catching any commands entered.
	std::string userInput(){
		std::string input{};
		std::cin >> input;
		if(input == "console"){
			experimental::console::startConsole();
			return "COMMAND_ENTERED";
	}
		else
			return input;
			
	}
	
	// This is used to clear the screen and reset any formatting changes.
	void clear() {
#if defined(Windows)
		COORD topLeft{ 0, 0 };
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;

		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacterA(
		    console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		FillConsoleOutputAttribute(
		    console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		    screen.dwSize.X * screen.dwSize.Y, topLeft, &written
		);
		SetConsoleCursorPosition(console, topLeft);
#elif defined(Linux)
		std::cout << "\x1B[2J\x1B[H";
#endif
		std::cout << termcolor::reset;
	}
	
	// Used to get the current Width of the console window 
	int getConsoleWidth(){
#if defined(Windows)
    	CONSOLE_SCREEN_BUFFER_INFO csbi;
    	int columns;
    	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    	return columns;
#elif defined(Linux)
    	struct winsize max;
    	ioctl(0, TIOCGWINSZ , &max);
    	return max.ws_col;
#endif
	}
	
	// Used to get the current Height of the console window
	int getConsoleHeight(){
		#if defined(Windows)
    	CONSOLE_SCREEN_BUFFER_INFO csbi;
    	int rows;
    	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return rows;
#elif defined(Linux)
		struct winsize max;
		ioctl(0, TIOCGWINSZ, &max);
		return max.ws.col
#endif
	}
};

#undef Windows
#undef MacOS
#undef Linux
#endif // CORE_H
