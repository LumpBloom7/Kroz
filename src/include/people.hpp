#ifndef PEOPLE_H
#define PEOPLE_H

#include <fstream>
#include <string>
#include "cereal/archives/json.hpp"

enum relationshipType {
    sibling,
    friends,
    enemies,
    partners,
    engaged,
    spouse,
    BFF,
    parent,
    child,
};
static const char *enumStrings[] = { "sibling", "friend", "enemies", " partners", "lover", "spouse", "best friend", "parent", "child"};

class Person {
	public:
		static std::shared_ptr<Person> makePerson();

		void changeDetails(std::string inputName, int inputAge, std::string inputGender) {
			name = inputName;
			age = inputAge;
			gender = inputGender;
		}
		void getDetails() {
			std::cout << "Name is " << name << ". This person is an " << age << " year old " << gender << "." << std::endl;
		}

		/*
				std::vector<relationshipType> relationships;
				std::vector<Person> relationshipPeople;
		*/
		std::string name{};
		int age{};
		std::string gender{};



		void save() {
			std::ofstream os(("testing/" + name + ".json"));
			cereal::JSONOutputArchive archive(os);

			archive( CEREAL_NVP(name),
			         CEREAL_NVP(age),
			         CEREAL_NVP(gender));  // Names the output the same as the variable name
		}
		void load() {
			std::ifstream is("testing/" + name + ".json");
			cereal::JSONInputArchive archive(is);

			archive( name, age, gender );
		}
};
class Follower : public Person {


};
static std::shared_ptr<Person> makePerson(int type) {
	switch(type) {
		case 0:
			return std::make_shared<Person>();
			break;
		case 1:
			return std::make_shared<Follower>();
			break;
		default:
			return std::make_shared<Person>();
			break;
	}
}
#endif // PEOPLE_H
