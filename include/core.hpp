#ifndef CORE_H
#define CORE_H

#include <fstream>
#include <sys/stat.h>
#include "cereal/archives/json.hpp"

#if defined(_WIN32) || defined(_WIN64)
#   define Windows
#	include "windows.h"
#	include <limits.h>
#elif defined(__APPLE__)
#   define MacOS
#elif defined(__unix__) || defined(__unix)
#   define Linux
#	include <sys/ioctl.h>
#	include <termios.h>
#	include <cstdlib>
#	include <unistd.h>
#else
#   error unsupported platform
#endif



namespace core {
	namespace filesystem { // Functions used to read and modify the file system of the user.
		inline bool fileExists (const std::string& fileName) // Used to check if a certain file exists with a certain directory
		{
			struct stat buffer;
			return (stat (fileName.c_str(), &buffer) == 0);
		}
	}
	namespace console {

		int getConsoleWidth() // Used to get the current Width of the console window
		{
#if defined(Windows)
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

			return columns;
#elif defined(Linux) // This should work on OSX too, but I have no way of testing it yet.
			struct winsize max;
			ioctl(0, TIOCGWINSZ, &max);
			return max.ws_col;
#endif
		}


		int getConsoleHeight() // Used to get the current Height of the console window
		{
#if defined(Windows)
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int rows;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			return rows;
#elif defined(Linux) // This should work on OSX too, but I have no way of testing it yet.
			struct winsize max;
			ioctl(0, TIOCGWINSZ, &max);
			return max.ws.col
#endif
		}
		void toggleEcho(bool enable) //Stops the console from printing anything if disabled.
		{
#ifdef WIN32
			HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
			DWORD mode;
			GetConsoleMode(hStdin, &mode);

			if( !enable )
				mode &= ~ENABLE_ECHO_INPUT;
			else
				mode |= ENABLE_ECHO_INPUT;

			SetConsoleMode(hStdin, mode );
#else
			struct termios tty;
			tcgetattr(STDIN_FILENO, &tty);
			if( !enable )
				tty.c_lflag &= ~ECHO;
			else
				tty.c_lflag |= ECHO;

			(void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
		}
		std::string getPassword(const char *prompt) // Used to get the password of the user without exposing what they typed.
		{
#if defined(Linux)
			std::string password = getpass(prompt);
#elif defined(Windows)
			std::cout << prompt << std::flush;
			std::string password;
			toggleEcho(false);
			std::cin >> password;
			toggleEcho(true);
#endif
			return password;
		}
	}
	void save() // Serialize namespace player
	{
		std::string password {};
		std::ofstream os(("saveData/" + player::userName + ".json"));
		cereal::JSONOutputArchive archive(os);

		archive( CEREAL_NVP(player::userName),
		         CEREAL_NVP(player::password),
		         CEREAL_NVP(player::experience)); // Names the output the same as the variable name
	}
	int load() // Deserialize namespace player
	{
		std::string userName {};
		std::cout << "Please enter your userName: " << std::flush;
		std::cin >> userName;
		if(core::filesystem::fileExists("saveData/" + userName + ".json")) {
			std::string password {""};
			std::ifstream is("saveData/" + userName + ".json");
			cereal::JSONInputArchive archive(is);
			archive(player::userName, player::password, player::experience);
			std::cout << player::password << std::endl;
			if(player::password != "") {
				std::string tempPassword = core::console::getPassword("Please input your password for your save file: ");
				std::cout << tempPassword << std::endl;
				if(tempPassword != player::password) {
					std::cout << termcolor::red << "The inputted password seems to be incorrect, please try again." << termcolor::reset << std::endl;
					return -1;
				}
			}
		} else {
			std::cout << termcolor::red << "It seems like there is no save files for that userName.." << termcolor::reset << std::endl;
			return -1;
		}
	}

	void clear() // This is used to clear the screen and reset any formatting changes.
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

	int createMenu(std::string title, std::vector<std::string> menuContent, bool backEnabled)  // Creates a menu without using the nCurses library, not likely to be efficient. Still needs linux code.
	{
		core::clear();
		int numberOfOptions = menuContent.size() - 1;
		int pointerCoord = 0;
		core::clear();
		std::cout << termcolor::bold << termcolor::underline
		          << title << termcolor::reset << std::endl;

		for(int a = 0; a < menuContent.size(); a++) {
			if(pointerCoord == a) {
#if defined(Linux) || defined(MacOS)
				std::cout << termcolor::on_grey;
#elif defined(Windows)
				std::cout << termcolor::green << "> ";
#endif
			}
			std::cout << menuContent[a] << termcolor::reset << std::endl;
		}
		bool failcheck{};
		while(true) {
			if((GetAsyncKeyState ( VK_UP ) & SHRT_MAX) && failcheck) {
				pointerCoord--;
				if(pointerCoord < 0)
					pointerCoord = numberOfOptions;
				core::clear();
				std::cout << termcolor::bold << termcolor::underline
				          << title << termcolor::reset << std::endl;
				for(int a = 0; a < menuContent.size(); a++) {
					if(pointerCoord == a) {
#if defined(Linux) || defined(MacOS)
						std::cout << termcolor::on_grey;
#elif defined(Windows)
						std::cout << termcolor::green << "> ";
#endif
					}
					std::cout << menuContent[a] << termcolor::reset << std::endl;
				}

			} else if((GetAsyncKeyState ( VK_DOWN ) & SHRT_MAX) && failcheck)  {
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
			} else if((GetAsyncKeyState ( VK_RETURN ) & SHRT_MAX)&& failcheck)  {
				std::cin.ignore();
				return pointerCoord;
			} else if((backEnabled == true) && ((GetAsyncKeyState ( VK_ESCAPE ) & SHRT_MAX)  && failcheck) ) {
				return -1;
			}
			failcheck = true;
		}
		return -1;
	}
}

#undef Windows
#undef MacOS
#undef Linux
#endif // CORE_H
