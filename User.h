// include your own comments

#ifndef _USER_H_
#define _USER_H_

#include <string>
#include <stdexcept>
#include "Person.h"
#include "DataManager.h"
using namespace std;

class User: public Person
{   public:
        // constructor should initialise name and registration number using arguments
        // and initialise score map to be empty
        User(const string &name, int regNo);

	   // method to return registration number
	   int getRegNo() const override;
    
    PersonType getType() const override; // useful while discrimating from creator
    unique_ptr<string> getKeyword();// returns the formatted keyword
    void getVideo(DataManager* datamanager);// get video option
    void getVideoRecommendations(DataManager* datamanager);// get video recommendation option
    void ask_video_update_likedis(DataManager* datamanager);// asks video and then updates its like or dislike
    void displayTrendingChannels(DataManager* datamanager);// trending channels option
    void showMenu(DataManager* datamanager);// main menu
    private:
	   int regNo;
	   string name;
    multimap<int,pair<string,float>> score;// stores int number to be able to discriminate and name and score

    
};

#endif
