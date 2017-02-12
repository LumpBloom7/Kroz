#ifndef STORYLINE_H
#define STORYLINE_H

#include <chrono>
#include <thread>
#include <algorithm>

int main(), terminal();
namespace systemFS { // Experimental gameplay mechanic to simulate an actually file system that will be used within the game.
	class File { // Virtual file for the terminal, will be stored in an std::vector located in the class Directory.
		public:
		static std::shared_ptr<File> makeFile();
			void changeDetails(std::string name)
			{
				fileName = name;
			}
			void changeDetails(bool isHidden)
			{
				hidden = isHidden;
			}
			void changeDetails(std::string name, bool isHidden)
			{
				fileName = name;
				hidden = isHidden;
			}
			void changeContents(std::string fileContent)
			{
				content = fileContent;
			}
			std::string getFileName()
			{
				return fileName;
			}
			bool getHiddenStatus()
			{
				return hidden;
			}
		private:
			bool hidden {};
			std::string content{};
			std::string fileName{};
	};
	static std::shared_ptr<File> makeFile()
	{
		return std::make_shared<File>();
	}
	class Directory { // Virtual directory for the terminal
		public:
			static std::shared_ptr<Directory> makeDirectory();
			std::string getName(){
				return name;
			}
			bool isHidden(){
				return hidden;
			}
			void changeDetails(std::string newName)
			{
				name = newName;
			}
			void changeDetails(bool isHidden)
			{
				hidden = isHidden;
			}
			void changeDetails(std::string newName, bool isHidden)
			{
				name = newName;
				hidden = isHidden;
			}
			std::vector< std::shared_ptr<Directory> > getSubDirectories(){
				return subDirectories;
			}
			std::string getFolderName(){
				return name;
			}
			void createDirectory(std::string directoryName){
				auto a = std::make_shared<Directory>();
				a -> changeDetails(directoryName);
				subDirectories.push_back(a);
			}
			void createDirectory(std::string directoryName, bool isHidden){
				auto a = std::make_shared<Directory>();
				a -> changeDetails(directoryName);
				a -> changeDetails(isHidden);
				subDirectories.push_back(a);
			}
		private:
			std::string name;
			bool hidden{};
			std::vector< std::shared_ptr<Directory> > subDirectories{};
			std::vector<std::shared_ptr<File>> files{};
	};
	static std::shared_ptr<Directory> makeDirectory(){
		return std::make_shared<Directory>();
	}
	
}
namespace chapter1 {


	int actions(), programsList();
	void bootupCinematics();

	int story() // Storyline
	{
		core::clear();
		std::cout << termcolor::magenta
		          << "You are a professional hacker" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "This is your story to get revenge" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << "Revenge on someone who stole your code.." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
		core::clear();
		std::cout << termcolor::magenta << termcolor::underline
		          << "Monday, 18th of April 2016" << std::endl;
		bootupCinematics();
		core::clear();
		if (player::userName == "") {
			std::cout << "Please register your new HackOS account..." << std::endl
			          << "Enter Username(Without spaces): " << std::flush;
			std::cin >> player::userName;
			std::string password = core::console::getPassword("Enter optional password: ");
		}
		actions();
		std::cin.get();
		std::cin.get();
		return 0;
	}
	int actions() // Lets the player interact with his virtual computer
	{
		std::vector<std::string> menu {"0. Terminal", "1. Programs", "2. E-Mail", "3. Internet", "4. ShutDown"};

		int results = core::createMenu("What do you want to do?", menu, true);

		switch (results) {
			case 0: {
					// Terminal
					//terminal();
				}
			case 1: {
					//Programs menu...
					programsList();
					break;
				}
			case 2: {
					//E-Mail interface
					break;
				}
			case 3: {
					//Internet browser that does not browse the web
					break;
				}
			case 4: {
					::main();
					return 0;
				}
			default: {
					actions();
				}
		}
		actions();
	}
	int terminal() // Experimental terminal functionality
	{
		core::clear();
		while(true) {
			std::cout << "Computer > " << std::flush;
			std::string command{};
			std::cin >> command;
			//Process command
			break;
		}
	}
	int programsList() // A list of shortcuts to usefull tools within the game
	{
		std::vector<std::string> menu{"E-Mail"};
		if(player::internetUnlocked) {
			menu.push_back("Internet");
		}
		if(player::passwordCracker) {
			menu.push_back("Password Cracker");
		}

		menu.push_back("Return");
		int results = core::createMenu("Programs", menu, true);
		switch (results) {
			case 0: {

				}
			case 1: {

				}
			case -1: {

				}
		}
	}
	void bootupCinematics() // Self explanatory
	{
		std::this_thread::sleep_for(std::chrono::seconds(3));
		core::clear();
		for (int x = 0; x < (core::console::getConsoleWidth() / 2) - 10; x++) {
			std::cout << "=" << std::flush;
		}
		std::cout << "HackOS v0.59.32 Beta" << std::flush;
		for (int x = 0; x < (core::console::getConsoleWidth() / 2) - 10; x++) {
			std::cout << "=" << std::flush;
		}
		std::cout << "Kernel loaded." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << termcolor::reset << "Loading core system files..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "Computer > System > processManager.sys started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > powerManager.sys started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > overClocker.sys started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > Drivers > genericDisplay.dri started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > Drivers > inputDrivers.dri started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > Drivers > networkCard.dri started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > Drivers > audioCard.dri failed to start due to lack of audio card." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > Drivers > piChipset.dri started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Computer > System > Network > networkInterface.sys started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > Network > rotVPN.paf started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > Network > wifiInterface.sys started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
		std::cout << "Computer > System > Network > macAddressChanger.paf started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > Network > remoteAccess.sys started" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > HackServices > MITMService.paf started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > HackServices > EMP.paf started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > HackServices > denialOfService.paf started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > Applications > ApplicationsService.sys started." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "Computer > System > stdUserInterface.sys started" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << termcolor::green << "Core systems file sucessfully loaded." << std::endl;

		for (int x = 0; x < core::console::getConsoleHeight(); x++) {
			std::cout << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
};
#endif
