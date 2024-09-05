//
//  main.cpp
//  Cpp2nd
//
//  Created by Berk Iskar on 04/01/2024.
//

#include <iostream>
#include "User.h"
#include "Creator.h"
#include "DataManager.h"
// template login function that works for both Creators and Users
template <typename persons>
persons login(ifstream& user_data, DataManager* datamanager, string* username, int& regno, int& choice){
    string line;
    string name;
    string surname;
    float channelScore;
    int newregno;
    // read the file and create new objects and store them in the vector inside of the datamanager class,
    // And I use this vector for everything, such as accessing data and updating files
    // this loop is to fill the vector
    while (getline(user_data, line)) {
        istringstream istr(line);
        
        if (istr >> newregno >> name) {
            
            if (istr >> surname) {
                name += " " + surname;
            }
            // if channelscore exists create creator
            if (istr >> channelScore) {
                
                Person* creator = new Creator(name,newregno);
                datamanager->push_back_person(creator);
            // if not create user
            } else {
                
                Person* user = new User(name,newregno);
                datamanager->push_back_person(user);
            }
        }
    }
    // For each person in file, and return the corresponding person
    for (Person* person : datamanager->getUsers()) {
        // If type is User do
        if (person->getType() == PersonType::User) {
            // static_cast, or dynamic_cast to create User to be able to access User specific functions
            User* userPtr = dynamic_cast<User*>(person);
            // if a person with the entered credentials exists create it
            if (person->getName() == *username && userPtr->getRegNo() == regno) {
                cout<<string(30,'-')<<endl;
                cout<<"Successfully logged in as User"<<endl;
                return persons(*username, regno);
            }
        // If type is Creator do
        } else if (person->getType() == PersonType::Creator) {
            // static_cast, or dynamic_cast to create User to be able to access Creator specific functions
            Creator* creatorPtr = dynamic_cast<Creator*>(person);
            // if a person with the entered credentials exists create it
            if (person->getName() == *username && creatorPtr->getRegNo() == regno) {
                cout<<string(30,'-')<<endl;
                cout<<"Successfully logged in as Creator"<<endl;
                return persons(*username, regno);
            }
        }
    }cout<<string(30,'-')<<endl;
    // if the person doesnt exist
    cout<<"It seems like you are not registered!"<<endl;
    // add the new User into database
    if(choice==1){
        cout<<"Creating a new 'User' account with the entered credentials."<<endl;
        Person* user = new User(*username, regno);
        datamanager->push_back_person(user);
    }
    // add the new Creator into database
    else if (choice==2){
        cout<<"Creating a new 'Creator' account with the entered credentials."<<endl;
        Person* creator = new Creator(*username, regno);
        datamanager->push_back_person(creator);
    }
    cout<<string(30,'-')<<endl;
    // return the new person
    return persons(*username, regno);
}
int main(int argc, const char * argv[]) {
    try{
        // to be able to manage data
        DataManager* datamanager = new DataManager;
        // extract youtube data to vector inside datamanager
        datamanager->youtube_data_to_vector();
        
        // user file
        ifstream user_data("users.txt");
        if (!user_data.is_open()){cout<<"File could not be opened"<<endl;terminate();}
        int* regno = new int;
        int* choice = new int;
        string* name =  new string;
        string* surname = new string;
        // need this if person with the entered credentials does not exist
        cout<<string(30,'-')<<endl;
        cout<< "How would you like to login?"<<endl;
        cout<<"1-> User\n2-> Creator"<<endl;
        cout<<string(30,'-')<<endl;
        cin>> *choice;
        // incase non int value entered, print message and terminate
        if (cin.fail()) {
            cerr << "Invalid input! Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            delete name;
            name = nullptr;
            delete surname;
            surname = nullptr;
            delete choice;
            choice = nullptr;return 0;}
        cout<<string(30,'-')<<endl;
        // Person name has to be 2 words, numbers can also be used
        cout<<"What's your full username(Enter 2 words)?"<<endl;
        cout<<string(30,'-')<<endl;
        cin>> *name>>*surname;
        // incase inappropriate value entered, print message and terminate
        if (cin.fail()) {
            cerr << "Invalid input! Please enter 2 words." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            delete name;
            name = nullptr;
            delete surname;
            surname = nullptr;
            delete choice;
            choice = nullptr;return 0;}
        // These 2 transforms are to make only the first char upper case others lower because thats how name's stored in file, otherwise cannot find the name if there is another uppercase
        transform(name->begin(), name->end(), name->begin(), ::tolower);
        if (!name->empty())(*name)[0] = ::toupper((*name)[0]);
        transform(surname->begin(), surname->end(), surname->begin(), ::tolower);
        if (!surname->empty())(*surname)[0] = ::toupper((*surname)[0]);
        
        cout<<string(30,'-')<<endl;
        // registration number to be able to access the corresponding person
        cout<<"Enter registration number:"<<endl;
        cin>>*regno;
        if (cin.fail()) {
            cerr << "Invalid input! Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            delete name;
            name = nullptr;
            delete surname;
            surname = nullptr;
            delete choice;
            choice = nullptr;
            return 0;}
        cout<<string(30,'-')<<endl;
        // combine name and surname, needed because thats the name saved in Person
        string* username = new string(*name += " " + *surname);
        
        // if logged in as user
        if(*choice == 1){
            // Create the user using template func
            User* user = new User(login<User>(user_data, datamanager, username,*regno,*choice));
            // show the main menu, which includes every function of users
            user->showMenu(datamanager);
            delete user;
            user = nullptr;
        }
        // if logged in as creator
        else if (*choice ==2){
            // Create the creator using template func
            Creator* creator = new Creator(login<Creator>(user_data, datamanager, username,*regno,*choice));
            // show the main menu, which includes every function of creators
            creator->showMenu(datamanager);
            delete creator;
            creator = nullptr;
        }
        else{cout<<string(30,'-')<<endl;cout<<"Invalid option! Can only be User or Creator. Please restart."<<endl;cout<<string(30,'-')<<endl;}
        
        
        // clean
        delete username;
        username = nullptr;
        delete name;
        name = nullptr;
        delete surname;
        surname = nullptr;
        delete choice;
        choice = nullptr;
        return 0;
        
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;}// if error occurs
       
}
