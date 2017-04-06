#ifndef CORE_H
#define CORE_H

namespace core {
	namespace filesystem { // Functions used to read and modify the file system of the user.
		bool fileExists(const std::string &fileName); // Used to check if a certain file exists with a certain directory
	}
	namespace console {
		int getConsoleWidth(); // Used to get the current Width of the console window
		int getConsoleHeight(); // Used to get the current Height of the console window
		void toggleEcho(bool enable); //Stops the console from printing anything if disabled.
		std::string getPassword(const char *prompt); // Used to get the password of the user without exposing what they typed.
		void executeCommand(std::string command);
	}
	void save(); // Serialize namespace player
	int load(); // Deserialize namespace player
	void clear(); // This is used to clear the screen and reset any formatting changes.
	int createMenu(std::string title, std::vector<std::string> menuContent, bool backEnabled); // Creates a menu without using the nCurses library, not likely to be efficient. Still needs linux code.

}

#endif // CORE_H
