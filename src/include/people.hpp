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
static const char *enumStrings[] = { "sibling", "friend", "enemies", " partners", "lover", "spouse", "best friend", "parent", "child"};

class Person {
public:

    static Person *makePerson();
    virtual void changeDetails(std::string inputName, int inputAge, std::string inputGender) = 0;
    virtual void getDetails() = 0;
    std::vector<Person*> relationships;
    std::vector<relationshipType> _relationships;
    std::string name;
    int age;
    std::string gender;

    //Relationships
    virtual void changeRelationship(char changeType, relationshipType relationship, Person* target) = 0;
    virtual std::string checkRelationship(Person* target) = 0;
};
class Follower : public Person {
    void changeDetails(std::string inputName, int inputAge, std::string inputGender)
    {
        name = inputName;
        age = inputAge;
        gender = inputGender;
    }
    void getDetails()
    {
        std::cout << "Name is " << name << ". This person is an " << age << " year old " << gender << "." << std::endl;
    }

    //Relationships.
    void changeRelationship(char changeType, relationshipType relationship, Person* target)
    {
        if(changeType == 'c') { //Change existing relationship
            bool found = false;
            for(int a = 0; a < relationships.size(); a++) {
                if(relationships[a] == target)
                    _relationships[a] = relationship;
            }
            if(!found) {
                std::cout << termcolor::red
                          << "ERROR: No relationship between target." << std::endl
                          << termcolor::reset
                          << "Press any key to continue..." << std::endl;
                std::cin.get();
                std::cin.get();
            }
        } else if(changeType == 'a') { //Add new relationship
            relationships.push_back(target);
            _relationships.push_back(relationship);
            target -> relationships.push_back(this);
            target -> _relationships.push_back(relationship);
        } else if(changeType == 'r') { //Remove existing relationship
            bool found = false;
            //Check for existing relationship
            for(int a = 0; a < relationships.size(); a++) {
                if(relationships[a] == target)
                    relationships.erase(relationships.begin()+ a);
                _relationships.erase(_relationships.begin()+ a);
                found = true;
            }
            if(!found) { //Relationship not found, tell them to add relationship
                std::cout << termcolor::red
                          << "ERROR: No relationship between target. Use \'a\' in changeType to add a relationship." << std::endl
                          << termcolor::reset
                          << "Press any key to continue..." << std::endl;
                std::cin.get();
                std::cin.get();
            }
        } else {
            std::cout << termcolor::red
                      << "ERROR: Invalid arguments inserted at \'char changeType\'" << std::endl
                      << termcolor::reset
                      << "Press any key to continue..." << std::endl;
        }
    }
    std::string checkRelationship(Person* target)   //Check Relationship between this and target
    {
        for(int a = 0; a < relationships.size(); a++) {
            if(relationships[a] == target) {
                std::string relation;
                if(relationships[a]-> gender == "male") { //This person is male, using masculine version of some words.
                    switch (_relationships[a]) {
                    case 0:
                        relation = "brother";
                        break;
                    case 4:
                        relation = "boyfriend";
                        break;
                    case 7:
                        relation = "father";
                        break;
                    case 8:
                        relation = "son";
                        break;
                    default:
                        relation = enumStrings[(_relationships[a])];
                        break;
                    }
                } else if(relationships[a]-> gender == "female") { //This person is female, using feminine version of some words
                    switch (_relationships[a]) {
                    case 0:
                        relation = "sister";
                        break;
                    case 4:
                        relation = "girlfriend";
                        break;
                    case 7:
                        relation = "mother";
                        break;
                    case 8:
                        relation = "daughter";
                        break;
                    default:
                        relation = enumStrings[(_relationships[a])];
                        break;
                    }
                } else { //Indeterminate gender, using default.
                    relation = enumStrings[_relationships[a]];
                }
                return (relationships[a]-> name + " is " + this-> name + "\'s " + relation + "."); //Returns a complete line describing their relationship
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
