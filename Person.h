// include your own comments

#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>

using namespace std;
// need to to be able to discrimate person referenced user and creator
enum class PersonType { User, Creator };
class Person
{   public:
        Person(const string &name);
	   string getName() const;
	   void changeName(const string &newName);
    virtual PersonType getType() const;// returns the type, User or Creator
    virtual ~Person() = default;// just to support dynamic_cast not necessary
    virtual int getRegNo() const; // virtual funct to access child regno
    virtual float getTotalRatio() const;// virtual funct to access child score
    protected:
	   string name;
   
};

#endif
