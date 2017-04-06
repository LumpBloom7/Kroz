#include "people.hpp"
#include <fstream>
#include <map>
#include "cereal/archives/json.hpp"

void Person::changeDetails(std::string inputName, int inputAge, std::string inputGender)
{
	name = inputName;
	age = inputAge;
	gender = inputGender;
}
void Person::getDetails()
{
	std::cout << "Name is " << name << ". This person is an " << age << " year old " << gender << "." << std::endl;
}
void Person::save()
{
	std::ofstream os(("testing/" + name + ".json"));
	cereal::JSONOutputArchive archive(os);

	archive(CEREAL_NVP(name),
	        CEREAL_NVP(age),
	        CEREAL_NVP(gender));  // Names the output the same as the variable name
}
void Person::load()
{
	std::ifstream is("testing/" + name + ".json");
	cereal::JSONInputArchive archive(is);

	archive(name, age, gender);
}
