#ifndef CORE_H
#define CORE_H

#if defined(_WIN32) || defined(_WIN64)
#   define Windows
#	include "windows.h"
#	include <limits.h>
#elif defined(__APPLE__)
#   define MacOS
#elif defined(__unix__) || defined(__unix)
#   define Linux

#	include <sys/ioctl.h>
#	include <cstdlib>
#else
#   error unsupported platform
#endif

#include <fstream>
#include "cereal/archives/json.hpp"
#include <stdio.h>
#include <stdlib.h>


namespace core {

	namespace experimental { // Experimental stuff

		namespace console {


			int health {100};
			int attackModifier {1};
			int defenseModifier {1};
			bool godMode {false};

			void save()
			{
				std::string name {".variables"};

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
			void startConsole()
			{
#if defined(Windows)
				ShellExecute(NULL, "open", "console\\KrozConsole.exe", NULL, NULL, SW_SHOWDEFAULT);//Need this to close as parent closes, need to use SendMessage();
#elif defined(Linux)
#endif
			}
		};
	}

	// This is used to handle user input while catching any commands entered.
	std::string userInput()
	{
		std::string input {};
		std::cin >> input;
		if(input == "console") {
			experimental::console::startConsole();
			return "COMMAND_ENTERED";
		} else
			return input;

	}

	// This is used to clear the screen and reset any formatting changes.
	void clear()
	{
#if defined(Windows)
		COORD topLeft { 0, 0 };
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


	std::string getPassword(const char *prompt)
	{
#if defined(Linux)
		std::string password = getpass(prompt);
#elif defined(Windows)
		const char BACKSPACE=8;
		const char RETURN=13;

		std::string password;
		unsigned char ch=0;

		std::cout << prompt << std::flush;

		DWORD con_mode;
		DWORD dwRead;

		HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);

		GetConsoleMode( hIn, &con_mode );
		SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

		while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN) {
			if(ch==BACKSPACE) {
				if(password.length()!=0) {
					std::cout <<"\b \b";
					password.resize(password.length()-1);
				}
			} else {
				password+=ch;

				std::cout <<'*';
			}
		}
		std::cout << std::endl;
		return password;
#endif
	}

	int createMenu(std::string title, std::vector<std::string> menuContent , bool backEnabled)
	{
		int numberOfOptions = menuContent.size() - 1;
		int pointerCoord = 0;
		core::clear();
		std::cout << termcolor::bold << termcolor::underline
		          << title << termcolor::reset << std::endl;

		for(int a = 0; a < menuContent.size(); a++) {
			if(pointerCoord == a) {
#if defined(Linux)
				std::cout << termcolor::on_grey;
#elif defined(Windows)
				std::cout << termcolor::green << "> ";
#endif
			}
			std::cout << menuContent[a] << termcolor::reset << std::endl;
		}
		while(true) {

			if(GetAsyncKeyState ( VK_UP ) & SHRT_MAX) {
				pointerCoord--;
				if(pointerCoord < 0)
					pointerCoord = numberOfOptions;
				core::clear();
				std::cout << termcolor::bold << termcolor::underline
				          << title << termcolor::reset << std::endl;
				for(int a = 0; a < menuContent.size(); a++) {
					if(pointerCoord == a) {
#if defined(Linux)
						std::cout << termcolor::on_grey;
#elif defined(Windows)
						std::cout << termcolor::green << "> ";
#endif
					}
					std::cout << menuContent[a] << termcolor::reset << std::endl;
				}

			} else if(GetAsyncKeyState ( VK_DOWN ) & SHRT_MAX) {

				pointerCoord++;
				if(pointerCoord > numberOfOptions)
					pointerCoord = 0;
				core::clear();
				std::cout << termcolor::bold << termcolor::underline
				          << title << termcolor::reset << std::endl;
				for(int a = 0; a < menuContent.size(); a++) {
					if(pointerCoord == a) {
#if defined(Linux)
						std::cout << termcolor::on_grey;
#elif defined(Windows)
						std::cout << termcolor::green << "> ";
#endif
					}
					std::cout << menuContent[a] << termcolor::reset << std::endl;
				}
			} else if(GetAsyncKeyState (VK_RIGHT) & SHRT_MAX) {
				return pointerCoord;
			} else if((backEnabled == true) && (GetAsyncKeyState (VK_LEFT) & SHRT_MAX)){
				return -1;
			}
		}
		return -1;
	}

// Used to get the current Width of the console window
	int getConsoleWidth()
	{
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
	int getConsoleHeight()
	{
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
