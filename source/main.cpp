#include <iostream>
#include <vector>
#include "termcolor.hpp"
#include "core.hpp"
#include "people.hpp"

void newGame(), continueGame(), chapterSelect(),userSelect(),quit();

int main()
{
    core::clear();
    std::cout << termcolor::reset
			  << "Welcome to Kroz. What would you like to do?" << std::endl
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
	else
		main();
    /*std::vector<Person*> people;
    people.push_back(Person::makePerson());
    people[0]-> changeDetails("Lorne", 14, "Male");
    people[0]-> getDetails();

    people.push_back(Person::makePerson());
    people[1]-> changeDetails("Derrick", 15, "Male");
    people[1]-> getDetails();

    people[1]-> addRelationship(relationshipType::sibling, people[0]);
    std::cout << people[1]-> checkRelationship(people[0]) << std::endl;
    std::cout << people[0]-> checkRelationship(people[1]) << std::endl;

    people.push_back(Person::makePerson());
    people[2]-> changeDetails("Colette", 21, "Female");
    people[2]-> getDetails();
    people[2]-> addRelationship(relationshipType::engaged, people[0]);
    std::cout << people[2]-> checkRelationship(people[0]) << std::endl;
    std::cout << people[0]-> checkRelationship(people[2]) << std::endl;

    people[1]-> addRelationship(relationshipType::friends, people[2]);
    std::cout << people[1]-> checkRelationship(people[2]) << std::endl;
    std::cout << people[2]-> checkRelationship(people[1]) << std::endl;*/


    return 0;
}
void newGame(){
	std::cout << termcolor::red
			  << "Are you sure you want to start a new game?" << std::endl
			  << "All saved games will be deleted." << std::endl
			  << termcolor::green
			  << "Please enter your choice(y/N): " <<std::flush;

	std::string playerReply;
	std::cin >> playerReply;
}
