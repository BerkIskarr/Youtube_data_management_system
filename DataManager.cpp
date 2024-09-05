//
//  DataManager.cpp
//  Cpp2nd
//
//  Created by Berk Iskar on 07/01/2024.
//

#include "DataManager.h"

#include "Creator.h"
#include "User.h"
// constructor
DataManager::DataManager(){lastVideoId = new int(1);}
// deconstructor for freeing memory
DataManager::~DataManager(){
    for (Person* person : Users) {
        delete person;
        person = nullptr;
        }
delete lastVideoId;lastVideoId = nullptr;}
int* DataManager::getLastVidID(){return this->lastVideoId;}// returns the lastvidid useful while creating new video
vector<Person*>& DataManager::getUsers(){return Users;}// returns users vector
vector<Video>& DataManager::getVideos(){return Videos;}// returns videos vector
void DataManager::push_back_video(Video& video){Videos.push_back(video);}// add into videos vector
void DataManager::push_back_person(Person *person){Users.push_back(person);}// add person into Users
void DataManager::increaseLastVidID(){(*this->lastVideoId)++;}// increase lastvidid 1
// from youtube data file to videos vector
void DataManager::youtube_data_to_vector(){
    try{
        ifstream youtube_data("fake_youtube_data_updated.txt");
        if (!youtube_data.is_open()){cout<<"File could not be opened"<<endl;return;}
        // to read the file line by line
        string* line= new string();
        
        int* number = new int(0);
        // to split line by ',' and add into the array, to assign into videos
        string **video_array = new string*[6];
        for (int i = 0; i < 6; ++i) {
            video_array[i] = new string;
        }
        // read the file and assign
        while(getline(youtube_data,*line)){
            istringstream ss(*line);
            // split the line
            while(getline(ss, *video_array[*number], ',')){
                (*number)++;
            }
            // create new video object using values in video_array
            Video video(video_array[0], video_array[1], video_array[2],new int(std::stoi(*video_array[3])),
                        new int(std::stoi(*video_array[4])),video_array[5]);
            // add video into the video vector data
            push_back_video(video);
            (*lastVideoId)++;
            // clear because need to save other lines
            for (int i = 0; i < 6; ++i) {
                video_array[i]->clear();
            }
            *number=0;
            line->clear();
        }
        
        youtube_data.close();
        // free memory
        delete number;
        number = nullptr;
        delete line;
        line = nullptr;
        
        delete video_array[0];
        delete video_array[1];
        delete video_array[2];
        delete video_array[3];
        delete video_array[4];
        delete video_array[5];
        delete[] video_array;
        video_array[0] = nullptr;
        video_array[1] = nullptr;
        video_array[2] = nullptr;
        video_array[3] = nullptr;
        video_array[4] = nullptr;
        video_array[5] = nullptr;
        video_array = nullptr;
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// update like or dislike of a specific video
void DataManager::updateLike_or_Dislike(Video& video,unique_ptr<string> likeordis){
    if(*likeordis=="like"){video.Like();cout<<"Thank you for liking!"<<endl;}
    else if (*likeordis=="dislike"){video.Dislike();cout<<"I did not like you either!"<<endl;}
}
// update user file
void DataManager::updateUserFile(){
    try{
    ofstream user_data("users.txt",ios::trunc);
    if (!user_data.is_open()){cout<<"File could not be opened"<<endl;return;}
    // check through persons in users vector
    for (Person* person : getUsers()) {
       
        // if type is User
        if (person->getType() == PersonType::User) {
            
            // can access some specific values now thanks to virtual functions inside person class
            user_data<<"000"<<person->getRegNo()<<" "<<person->getName()<<endl;
        }
        // if type is creator
        else if (person->getType() == PersonType::Creator) {
            
            // can access some specific values now thanks to virtual functions inside person class
            user_data<<person->getRegNo()<<" "<<person->getName()<<" "<<person->getTotalRatio()<<endl;
                }}
    user_data.close();
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}

// updating youtube video data file
void DataManager::updateVideosFile(){
    try{
    ofstream youtube_data("fake_youtube_data_updated.txt",ios::trunc);
    if (!youtube_data.is_open()){cout<<"File could not be opened"<<endl;return;}
    // write each of the video
    for (Video& video : this->getVideos()) {
            youtube_data << video;
        }
    youtube_data.close();
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// update video name
void DataManager::updateVideo(string* ID, string* newName){
    try{
    // search and if found update the name
    for(Video& video: this->getVideos())
        if(*video.getVideo_id()==*ID){
            video.setName(newName);
        }
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// update like and dislike
void DataManager::updateVideo(string* ID, int* like,int*dislike){
    try{
    // search and if found update like and dislike
    for(Video& video: this->getVideos())
        if(*video.getVideo_id()==*ID){
            video.setLike(like);
            video.setDislike(dislike);
        }
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// delete the video
void DataManager::updateVideo(string* ID) {
    try{
    // if  video found delete from the vector
    auto it = remove_if(Videos.begin(), Videos.end(),[ID](const Video& video) { return *video.getVideo_id() == *ID; });
    if (it != Videos.end()) {Videos.erase(it, Videos.end());
        cout << "Video is deleted!" << endl;
    } else {cout << "Video could not been deleted!" << endl;}
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}



