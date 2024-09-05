// include your own comments

#include <string>
#include "Person.h"

using namespace std;

Person::Person(const string &name)
{   this->name = name;
}

string Person::getName() const
{   return name;
}

void Person::changeName(const string &newName)
{   name = newName;
}
// need to to be able to discrimate users and creators
PersonType Person::getType() const{
    // randomly returned user, doesnt matter will be overriden
    return PersonType::User;
}
// need to access reg no of child classes, so virtual func
int Person::getRegNo() const{
    return 0; //random value does not matter
}
// need to access score of child classes, so virtual
float Person::getTotalRatio() const{
    return 1.0f;// random value does not matter
}
