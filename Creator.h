// include your own comments

// NOTE THIS CLASS IN INCOMPLETE, YOU SHOULD AIM TO COMPLETE ITS DEFINITION

#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "Person.h"
#include "DataManager.h"
using namespace std;

class NoScoreException: public exception
{
private:
    string msg;
public:
    NoScoreException(const string& msg) throw();
    const char* what() const noexcept override;
};


class Creator: public Person
{  public:
    // initialises name and registration number using arguments
    Creator(const string &channel_name, int regNo);
    // method to return registration number
    int getRegNo() const override;
    // method to add the score to the map
    void addScore(float score,string video_name);
    // method to update the accumulative score map, did not need this function
    bool updateLikeDislikeRatio();
    // main menu of the class
    void showMenu(DataManager* datamanager);
    // updates score
    void setTotalRatio(const float& newtotal);
    // returns the score
    float getTotalRatio()const override;
    // returns the name
    string& getChannelName();
    // returns the set
    set<Video> getAllVideos() const;
    // returns the type, handy to differ from User
    PersonType getType() const override;
    // custom iterator to iterate through multimap
    class iterator;
    friend class iterator;

    class iterator {
        using iterator_category = std::bidirectional_iterator_tag;// tag category, bidirectional for maps
        using value_type = std::pair<string, float>; // define type
        using difference_type = ptrdiff_t;
        using pointer = const pair<const string, float>*;
        using reference = const pair<const string, float>&;
        // "typename" necessary to resolve nesting
        typename multimap<string, float>::iterator it;
        multimap<string, float>* r;
        
    public:
        // constructor
        iterator(multimap<string, float>& map,
                 const typename multimap<string, float>::iterator& i);
        
        bool operator==(const iterator& x) const;
        
        bool operator!=(const iterator& x) const;
        
        std::pair<const string, float>& operator*() const;
        
        iterator& operator++();
        
        iterator operator++(int);
        
        iterator& operator--();
        
        iterator operator--(int);
        
        iterator insert(const pair<const string, float>& x);
        iterator erase();};
    void insert(float score,string video_name) {
        videos_and_ratios.insert({video_name, score});
    }

    iterator begin();// reference to first
    iterator end();// reference to last
    size_t size();// size of the map
    
    void createVideo(DataManager* datamanager);// create a video option
    void manageVideo(DataManager* datamanager);// manage a video optiom
    float calculateTotalRatio(); // calculates score
    void showChannelScore(); // displays channel score
    void fillallVideos(DataManager* datamanager); // fills multimap and set with all of the videos of the channel
    void fillMap(DataManager* datamanager);// fill only multimap with the creator's videos
    private:
	   int regNo;
	   string channel_name;
	   multimap<string,float> videos_and_ratios;  // scores map, having the video_name and its ratio
	   float like_dislike_ratio_total; // overall channel score 
       set<Video> allVideos; // to store all the videos of the creator, easier to access
       
	// friend function to output details of creator to stream
    friend ostream& operator<<(ostream &str, Creator &s);
};

#endif
