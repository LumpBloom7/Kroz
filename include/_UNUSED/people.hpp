#ifndef PEOPLE_H
#define PEOPLE_H

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
static const char* enumStrings[] = { "sibling", "friend", "enemies", " partners", "lover", "spouse", "best friend", "parent", "child"};

class Person {
	public:

		void changeDetails(std::string inputName, int inputAge, std::string inputGender);
		void getDetails();

		std::string name{};
		int age{};
		std::string gender{};

		void save();
		void load();
};

#endif // PEOPLE_H
