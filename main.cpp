#include <iostream>
#include <vector>
#include "termcolor.hpp"
#include "core.hpp"
#include "people.hpp"

using namespace std;

int main()
{
    /*core::clear();
    std::cout << "Welcome to Kroz. What would you like to do?" << std::endl
              << "1. New game" << std::endl
              << "2. Continue" << std::endl
              << "3. Select chapter" << std::endl
              << "4. Select user" << std::endl
              << "5. Quit" << std::endl
              << termcolor::green
              << "Please enter your selecion(1,2,3,4,5): " << std::flush;

    string playerReply;
    std::cin >> playerReply;*/

    std::vector<Person*> people;
    people.push_back(Person::makePerson());
    people[0]-> changeDetails("Lorne", 14, "Male");
    people[0]-> getDetails();
}
