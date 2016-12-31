#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "termcolor.hpp" // This header contains the functionality of adding colors to 'std::cout'.
#include "core.hpp" // This header contains the core functionality of the game engine.
#include "people.hpp" // This header contains the people factory and personality system.
#include "storyline.hpp" // This header contains the storyboard data for the game.


void newGame(), continueGame(), chapterSelect(),userSelect(),quit();

int main()
{
    core::clear(); // Clear the console of anything before loading the main menu.
    std::vector<std::string> menu {"New game", "Continue", "Select chapter", "Select user", "Debug", "Quit"};
    // Prints main menu, duh...
    int playerReply = core::createMenu("Welcome to Kroz. What would you like to do?", menu, false);

	switch(playerReply){
		case 0:{
			newGame();
			break;
		}
		case 1:{
			continueGame();
			break;
		}
		case 2:{
			chapterSelect();
			break;
		}
		case 4:{
			core::clear();
        	std::vector<std::shared_ptr<Person>> people;
	        people.push_back(makePerson(0));
    	    people[0]-> changeDetails("Lorne", 14, "male");
        	people[0]-> getDetails();

        	people.push_back(makePerson(0));
        	people[1]-> changeDetails("Derrick", 15, "male");
        	people[1]-> getDetails();

        	people.push_back(makePerson(0));
        	people[2]-> changeDetails("Colette", 21, "female");
        	people[2]-> getDetails();

        	for(int x = 0; x < people.size(); x++) {
            	people[x]-> save();
        	}
        	std::cin.get();
        	std::cin.get();

        	for(int x = 0; x < people.size(); x++) {
            	people[x]-> load();
        	}
        	people[0]-> getDetails();
        	people[1]-> getDetails();
        	people[2]-> getDetails();
        
        	core::experimental::console::save();
        	core::experimental::console::startConsole();
        	std::cin.get();
        	std::cin.get();
        	main();
        	break;
        }
		default:{
        	main();
        	break;
        }
	}
    return 0;
}
void newGame()
{
    core::clear();
    std::cout << termcolor::red << termcolor::blink
              << "WARNING: All saved games will be deleted." << std::endl
              << termcolor::reset << termcolor::red
              << "Are you sure you want to start a new game?" << std::endl
              << termcolor::green
              << "Please enter your choice(y/N): " <<std::flush;

    std::string playerReply{};
    std::cin >> playerReply;

    if(playerReply == "N" || playerReply == "n")
        main();
    else if(playerReply == "Y" || playerReply == "y"){
    	int result = chapter1::story();
    	if(result == -1)
    		main();
	}
    else {
        std::cout << termcolor::red
                  << "ERROR: Invalid response." << std::endl
                  << termcolor::reset
                  << "Press any key to continue..." << std::endl;

        std::cin.get();
        std::cin.get();

        newGame();
    }
}
void continueGame()
{
    core::clear();
    int lastPlayedChapter{};
    switch(lastPlayedChapter) {
    /*case 1:
    	int result = chapter1::story();
    	if(result == -1)
    		main();
    	break;
    case 2:
    	chapter2();
    	break;
    case 3:
    	chapter3();
    	break;
    case 4:
    	chapter4();
    	break;*/
    default:
        std::cout << termcolor::red
                  << "ERROR: No previous game session detected on this computer" << std::endl
                  << termcolor::reset
                  << "Please select \"New Game\" to start a new adventure" << std::endl
                  << termcolor::reset
                  << "Press any key to continue..." << std::endl;
        std::cin.get();
        std::cin.get();
        main();
        break;
    }
}
void chapterSelect()
{
    core::clear();
    bool chapter2Unlocked{}, chapter3Unlocked{}, chapter4Unlocked{};
	std::vector<std::string> menu {"0. Prologue", "1. Terminal"};
    if(chapter3Unlocked)
        menu.push_back("2. Superuser");
    else
        menu.push_back("2. <LOCKED>");

    if(chapter4Unlocked)
        menu.push_back("3. Bootloader");
    else
        menu.push_back("3. <LOCKED>");
    
    int playerReply = core::createMenu("Chapter select", menu, true);

    switch(playerReply){
    	case 0:{
    		std::cout << "0. Prologue" << std::endl;
    		break;
    	}
    	case 1:{
    		int result = chapter1::story();
    		if(result == -1)
    			main();
			break;
		}
		case 2:{
			std::cout << "2. Superuser" << std::endl;
			break;
		}
		case 3:{
			std::cout << "3. Bootloader" << std::endl;
			break;
		}
		case -1:{
			main();
			break;
		}
		default:{
			chapterSelect();
			break;
		}
    }
}

