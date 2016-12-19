#ifndef STORYLINE_H
#define STORYLINE_H

#include <chrono>
#include <thread>

namespace chapter1 {
	void actions(), bootupCinematics();
	void story() {
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
		std::cin.get();
		std::cin.get();

	}
	void actions() {
		//std::cout <<
	}
	void bootupCinematics() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		core::clear();
		for(int x = 0; x < (core::getConsoleWidth()/2) - 10; x++) {
			std::cout << "=" << std::flush;
		}
		std::cout << "HackOS v0.59.32 Beta" << std::flush;
		for(int x = 0; x < (core::getConsoleWidth()/2) - 10; x++) {
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

		for(int x = 0; x < core::getConsoleHeight(); x++) {
			std::cout << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
};
#endif
