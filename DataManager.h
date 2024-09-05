//
//  DataManager.h
//  Cpp2nd
//
//  Created by Berk Iskar on 07/01/2024.
//

#ifndef DataManager_h
#define DataManager_h

#include "Video.h"
#include "Person.h"

using namespace std;
// class for managing data
class DataManager{
protected:
    vector<Video> Videos; // storing all the videos in youtube videos file
    vector<Person*> Users; // store all the users in the file
    int* lastVideoId; // needed while creating new video
public:
    DataManager();
    ~DataManager();
    int* getLastVidID();// returns lastvidid
    void increaseLastVidID();
    void youtube_data_to_vector();
    void push_back_person(Person* person);
    vector<Person*>& getUsers();
    vector<Video>& getVideos();
    void push_back_video(Video& video);
    void updateLike_or_Dislike(Video& video,unique_ptr<string> likeordis);// update like or dislike

    
    void updateVideo(string* ID, string* newName);// update name of a video
    void updateVideo(string* ID, int* like,int*dislike);// update like or dislike of a video
    void updateVideo(string* ID);// delete a video
    void updateVideosFile();
    void updateUserFile();
    
};
#endif /* DataManager_h */
