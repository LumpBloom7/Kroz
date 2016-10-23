#if defined(_WIN32) || defined(_WIN64)
#   define Windows
#	include "windows.h"
#elif defined(__APPLE__)
#   define MacOS
#elif defined(__unix__) || defined(__unix)
#   define Linux
#else
#   error unsupported platform
#endif

#include <iostream>
#include <fstream>
#include <string>
#include "cereal/archives/json.hpp"
#include "termcolor.hpp"
std::string name = ".variables";
int health;
int attackModifier;
int defenseModifier;
bool godMode = false;
bool cheats = false;
bool debugMode = false;
bool thereIsNoMonkey = false; // Makes the game unaware of user actions in the console. Debugging purposes only, would be hidden from end-users.
std::string input;
void saveVariables() {


	std::ofstream os(("console\\" + name + ".json"));
	cereal::JSONOutputArchive archive(os);

	archive( CEREAL_NVP(health),
	         CEREAL_NVP(attackModifier),
	         CEREAL_NVP(defenseModifier),
	         CEREAL_NVP(godMode),
	         CEREAL_NVP(cheats),
	         CEREAL_NVP(debugMode),
			 CEREAL_NVP(thereIsNoMonkey)); // Names the output the same as the variable name
}
void loadVariables() {
	std::ifstream is("console\\" + name + ".json");
	cereal::JSONInputArchive archive(is);

	archive( health, attackModifier, defenseModifier, godMode );
}
void clear() {
#if defined(Windows)
	COORD topLeft  = { 0, 0 };
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
	std::cout << "\x1B[2J\x1B[H"
			  << termcolor::bold << termcolor::underline << "Kroz console" << std::endl;
#endif
	std::cout << termcolor::reset
			  << termcolor::bold << termcolor::underline << "Kroz console" << std::endl;
}


int main() {
	::loadVariables();
	std::cout << termcolor::bold << termcolor::underline << "Kroz console" << std::endl;
readCommand:
	std::cout << termcolor::reset << termcolor::green << ">" << std::flush;
	std::cin >> input;
	
	if(input == "SAVEVAR")
		::saveVariables();
	else if(input == "LOADVAR")
		loadVariables();
	else if(input == "set"){
		std::cin >> input;
		if(input == "health")
			std::cin >> health;
		else if(input == "attackModifier")
			std::cin >> attackModifier;
		else if(input == "defenseModifier")
			std::cin >> defenseModifier;
		else
			std::cout << termcolor::red << termcolor::blink << "No such variable..." << std::endl;
	}
	else if(input == "wuss")
		std::cin >> cheats;
	else if(input == "godmode")
		std::cin >> godMode;
	else if(input == "debug")
		std::cin >> debugMode;
	else if(input == "clear")
		::clear();
	else if(input == "ThereIsNoMonkey")
		std::cin >> thereIsNoMonkey;
	else if(input == "VARLIST") {
		std::cout << termcolor::reset
		          << "These variables are not saved yet, use SAVEVAR to save it or use LOADVAR to use unsaved settings." << std::endl
		          << "Health: " << health << std::endl
		          << "Attack modifier: " << attackModifier << std::endl
		          << "Defense modifier: " << defenseModifier << std::endl
		          << "God mode: " << godMode << std::endl
		          << "Cheats enabled: " << cheats << std::endl
		          << "Debug mode: " << debugMode << std::endl
		          << "Stealth command execution: " << thereIsNoMonkey << std::endl;
	} else
		std::cout << termcolor::red << "Command not found..." << std::endl;
		
	goto readCommand;
	return 0;
}
