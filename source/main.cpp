#include <iostream>
#include <vector>
#include "termcolor.hpp" //This header contains the functionality of adding colors to 'std::cout'.
#include "core.hpp" //This header contains the core functionality of the game engine.
#include "people.hpp" //This header contains the people factory and personality system.

void newGame(), continueGame(), chapterSelect(),userSelect(),quit();

int main()
{
    core::clear();
    std::cout << "Welcome to Kroz. What would you like to do?" << std::endl
              << "1. New game" << std::endl
              << "2. Continue" << std::endl
              << "3. Select chapter" << std::endl
              << "4. Select user" << std::endl
              << "5. Quit" << std::endl
              << termcolor::green
              << "Please enter your selecion(1,2,3,4,5): " << std::flush;

    std::string playerReply;
    std::cin >> playerReply;

    if(playerReply == "1")
        newGame();
    else if(playerReply == "2001") { //Debug every funtion
        core::clear();
        std::vector<Person*> people;
        people.push_back(Person::makePerson());
        people[0]-> changeDetails("Lorne", 14, "male");
        people[0]-> getDetails();

        people.push_back(Person::makePerson());
        people[1]-> changeDetails("Derrick", 15, "male");
        people[1]-> getDetails();

        people[1]-> changeRelationship('a', relationshipType::sibling, people[0]);
        std::cout << people[1]-> checkRelationship(people[0]) << std::endl;
        std::cout << people[0]-> checkRelationship(people[1]) << std::endl;

        people.push_back(Person::makePerson());
        people[2]-> changeDetails("Colette", 21, "female");
        people[2]-> getDetails();
        people[2]-> changeRelationship('a', relationshipType::engaged, people[0]);
        std::cout << people[2]-> checkRelationship(people[0]) << std::endl;
        std::cout << people[0]-> checkRelationship(people[2]) << std::endl;

        people[1]-> changeRelationship('a', relationshipType::friends, people[2]);
        std::cout << people[1]-> checkRelationship(people[2]) << std::endl;
        std::cout << people[2]-> checkRelationship(people[1]) << std::endl;

    } else
        main();

    return 0;
}
void newGame()
{
    core::clear();
    std::cout << termcolor::red
              << "Are you sure you want to start a new game?" << std::endl
              << "All saved games will be deleted." << std::endl
              << termcolor::green
              << "Please enter your choice(y/N): " <<std::flush;

    std::string playerReply;
    std::cin >> playerReply;

    if(playerReply == "N" || playerReply == "n")
        main();
    else if(playerReply == "Y" || playerReply == "y")
        std::cout << "chapter 1" << std::endl;
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
