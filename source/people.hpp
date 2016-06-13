#ifndef PEOPLE_H
#define PEOPLE_H

#include <vector>
using namespace std;
enum relationshipType
{
	sibling,
	friends,
	enemies,
	partners,
	engaged,
	spouse,
	BFF
};
static const char * EnumStrings[] = { "siblings", "friends", "enemies", " partners", "engaged", "spouse","Best friends" };
const char * relationStr( int enumVal )
{
  return EnumStrings[enumVal];
}



class Person
{
public:

    static Person *makePerson();
    virtual void changeDetails(std::string inputName, int inputAge, std::string inputGender) = 0;
    virtual void getDetails() = 0;
    std::vector<Person*> relationships;
	std::vector<relationshipType> _relationships;
    std::string name;
    int age;
    std::string gender;
    //Relationships are in development.
	virtual void addRelationship(relationshipType relationship, Person* target) = 0;
    virtual void removeRelationship(Person* target) = 0;
    virtual void changeRelationship(relationshipType relationship, Person* target) = 0;
    virtual std::string checkRelationship(Person* target) = 0;
};
class Follower : public Person
{
    void changeDetails(std::string inputName, int inputAge, std::string inputGender){
        name = inputName;
        age = inputAge;
        gender = inputGender;
    }
	void getDetails(){
        std::cout << "Name is " << name << ". This person is an " << age << " year old " << gender << "." << std::endl;
    }
    //Relationships are in development.
    void addRelationship(relationshipType relationship, Person* target){
    	relationships.push_back(target);
    	_relationships.push_back(relationship);
    	target -> relationships.push_back(this);
    	target -> _relationships.push_back(relationship);
	}
	void removeRelationship(Person* target){

	}
	void changeRelationship(relationshipType relationship, Person* target){

	}
	std::string checkRelationship(Person* target){
        for(int a = 0; a < relationships.size(); a++){
            if(relationships[a] == target){
                return ("The relationship between " + this-> name + " and " + relationships[a]-> name + " is " + relationStr(_relationships[a]) + ".");
                break;
            }
        }
	}
};
Person *Person::makePerson()
{
    return new Follower;
}
#endif // PEOPLE_H
