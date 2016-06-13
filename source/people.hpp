#ifndef PEOPLE_H
#define PEOPLE_H

class Person
{
    public:
    static Person *makePerson();
    virtual void changeDetails(std::string inputName, int inputAge, std::string inputGender) = 0;
    virtual void getDetails() = 0;
    std::string name;
    int age;
    std::string gender;
};
class Follower : public Person
{
    void changeDetails(std::string inputName, int inputAge, std::string inputGender){
        name = inputName;
        age = inputAge;
        gender = inputGender;
    }
     void getDetails(){
        std::cout << "Name is " << name << ". This person is an " << age << " year old " << gender << ".";
    }
};
Person *Person::makePerson()
{
    return new Follower;
}
#endif // PEOPLE_H
