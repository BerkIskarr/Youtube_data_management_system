////
////  Creator.cpp
////  Cpp2nd
////
////  Created by Berk Iskar on 04/01/2024.
////
//
#include "Creator.h"
// in case there is no score use this exception
NoScoreException::NoScoreException(const string& msg)throw(): msg(msg){}
// override .what() and print the message
const char* NoScoreException::what() const noexcept  {
    return msg.c_str();
}
// constructor
Creator::Creator(const string &channel_name, int regNo): Person(channel_name), regNo(regNo), like_dislike_ratio_total(0){}
int Creator::getRegNo() const{return this->regNo;}// returns regno
float Creator::getTotalRatio()const{return this->like_dislike_ratio_total;}// returns score
void Creator::setTotalRatio(const float& newtotal){this->like_dislike_ratio_total= newtotal;}//updates score
set<Video> Creator::getAllVideos() const{return this->allVideos;}// returns allVideos
string& Creator::getChannelName(){return this->channel_name;}// returns channel name
// main menu
void Creator::showMenu(DataManager* datamanager){
    try{
        // fill the set and multimap
        fillallVideos(datamanager);
        // calculate score and update the attribute
        float* sum = new float(0.0);
        *sum = this->calculateTotalRatio();
        this->setTotalRatio(*sum);
        delete sum;
        sum = nullptr;
        int* choice = new int;
        // cout infos
        cout<<string(30,'-')<<endl;
        cout<<"Welcome "<< getName()<<"!"<<endl;
        cout<<string(30,'-')<<endl;
        cout<<*this;
        cout<<string(30,'-')<<endl;
        while(true){
            
            cout<<"\nWhat can I do for you?\n"<<endl;
            cout<<"1- Show Channel Score"<<endl;
            cout<<"2- Create a Video"<<endl;
            cout<<"3- Manage a Video"<<endl;
            cout<<"4- Exit"<<endl;
            cout<<string(30,'-')<<endl;
            cin>>*choice;
            if (cin.fail()) {
                cerr << "Invalid input! Please enter an integer." << endl;
                cerr<<"Restarting..."<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');return;}
            // show channel score
            if(*choice==1){
                cout<<string(30,'-')<<endl;
                showChannelScore();
            }
            // create video
            else if (*choice==2){
                createVideo(datamanager);
            }
            // manage video
            else if (*choice==3){
                if(!this->getAllVideos().empty()){
                    manageVideo(datamanager);}
                else{cout<< "You do not have any videos yet!"<<endl;
                    cout<<string(30,'-')<<endl;}
            }
            // terminates the program
            else if (*choice==4){delete choice;
                choice = nullptr;cout<<"Hope to see you again, bye!"<<endl;cout<<string(30,'-')<<endl;return;}
            else{cout<<"Invalid option! Re enter"<<endl;}
        }}catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
 
}
// insert into the multimap
void Creator::addScore(float score,string video_name){
    insert(score,video_name);
}
// To fill both multimap and all videos set with all of its videos
void Creator::fillallVideos(DataManager* datamanager){
    for(Video& video:datamanager->getVideos()){
        if(*video.getChannelname() == this->getName()){
            allVideos.insert(video);
            addScore(video.getVideo_score(), *video.getVideo_name());
        }
    }
}
// to only fill the multimap
void Creator::fillMap(DataManager* datamanager){
    for(Video& video:datamanager->getVideos()){
        if(*video.getChannelname() == this->getName()){
            addScore(video.getVideo_score(), *video.getVideo_name());
        }
    }
}
// returns the type, handy to discriminate from users
PersonType Creator::getType() const {
       return PersonType::Creator;
}
// Calculate score using the custom iterator
float Creator::calculateTotalRatio() {
    try{
        // There are 2 ways to do this:
        
/*        float sum = accumulate(begin(), end(), 0.0, [](float cur, const auto& video) {
                        return cur + video.second;
                   });
 */
        // or
        Creator::iterator it = begin();
        it = begin();
        float sum = 0.0;
        for (int i = 0; i < size(); i++)
            sum += (*it++).second;
        sum /= size();
        return sum;
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;terminate();}
}

// updates channel score and then prints
void Creator::showChannelScore(){
    try{
        float* sum = new float(0.0);
        // calculate the score
        *sum = this->calculateTotalRatio();
        // assign to the variable
        this->setTotalRatio(*sum);
        delete sum;
        sum = nullptr;
        
        cout<<"Your Channel score is >> "<<this->like_dislike_ratio_total<<endl;
        cout<<string(30,'-')<<endl;
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}

// create video and update everything
void Creator::createVideo(DataManager* datamanager){
    try{
        // vid name has to be 2 words so save 2 inputs then combine
        string* vidName = new string;
        string* vidDuration = new string;
        string* vidName2 = new string;
        
        // use this to be able to create a unique vid ID, such as if the last one is video_1000, this will create video_1001 so video_1001 is the new video's id now.
        datamanager->increaseLastVidID();
        // LastVidID is for last id number, like 1000
        string* vidID = new string("video_"+to_string(*datamanager->getLastVidID()));
        
        cout<<"Enter the name of the video(Enter 2 words) "<<endl;
        cin>> *vidName>> *vidName2;
        cout<<"Enter video duration (Format: '00:00') "<<endl;
        cin>> *vidDuration;
        // combine two names because has to be 2 words
        *vidName=*vidName+" "+*vidName2;
        string *newName=new string(getName());
        Video* newVideo = new Video(vidID,vidName,vidDuration, new int(0),new int(0),newName);
        // add into map
        addScore(0.0f, *vidName);
        // add into set
        allVideos.insert(*newVideo);
        // add into our main data vector
        datamanager->push_back_video(*newVideo);
        float* sum = new float(0.0);
        *sum = this->calculateTotalRatio();
        // update score
        this->setTotalRatio(*sum);
        // update files
        datamanager->updateVideosFile();
        datamanager->updateUserFile();
        
        cout<<string(30,'-')<<endl;
        cout<<"Video is created"<<endl;
        cout<<string(30,'-')<<endl;
        delete sum;
        sum =nullptr;
        delete vidID;
        vidID = nullptr;
        delete vidName;
        vidName = nullptr;
        delete vidDuration;
        vidDuration = nullptr;
        delete newVideo;
        newVideo = nullptr;
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// Display all videos to the creator and ask if they wish to: a) rename a video, b) reset likes/dislikes and c) delete the video.
void Creator::manageVideo(DataManager* datamanager){
    try{
        char* choice = new char;
        set<Video>* vidSet = new set<Video>();
        for(Video& video:datamanager->getVideos()){
            if(*video.getChannelname() == this->getName()){
                vidSet->insert(video);
            }
        }
        
        while(true){
            cout<<string(30,'-')<<endl;
            for(Video video: *vidSet){
                cout<<video;
            }
            cout<<string(30,'-')<<endl;
            cout<<"a) rename a video"<<endl;
            cout<<"b) reset likes/dislikes"<<endl;
            cout<<"c) delete the video"<<endl;
            cout<<"d) go back"<<endl;
            cin>>*choice;
            cout<<string(30,'-')<<endl;
            // for renaming a video
            if(*choice=='a'){
                string* selectedVidID = new string;
                cout<<"Enter the exact ID of which video's name would you like to change"<<endl;
                cin>>* selectedVidID;
                
                string* newName = new string;
                string* newName2 = new string;
                cout<<"Enter the new name(Enter 2 words) "<<endl;
                cin>>*newName>>*newName2;
                *newName=*newName+" "+*newName2;
                
                datamanager->updateVideo(selectedVidID, newName);
                // reinitialize both multimap and set
                allVideos.clear();
                videos_and_ratios.clear();
                fillallVideos(datamanager);
                // update score
                float* sum = new float(0.0);
                *sum = this->calculateTotalRatio();
                this->setTotalRatio(*sum);
                
                // update files
                datamanager->updateVideosFile();
                datamanager->updateUserFile();
                cout<<string(30,'-')<<endl;
                cout<<"Name is changed!"<<endl;
                cout<<string(30,'-')<<endl;
                delete sum;
                sum = nullptr;
                delete selectedVidID;
                selectedVidID = nullptr;
                delete newName;
                newName = nullptr;
                delete newName2;
                newName2 = nullptr;
                
                break;}
            // for reset like/dislike
            else if (*choice =='b'){
                string* selectedVidID = new string;
                cout<<"Enter the exact ID of which video's like/dislike would you like to reset"<<endl;
                cin>>* selectedVidID;
                
                // updates the video
                datamanager->updateVideo(selectedVidID, new int(0), new int(0));
                // reinitialize the set and multimap, to update
                allVideos.clear();
                videos_and_ratios.clear();
                fillallVideos(datamanager);
                float* sum = new float(0.0);
                *sum = this->calculateTotalRatio();
                this->setTotalRatio(*sum);
                delete sum;
                sum = nullptr;
                datamanager->updateVideosFile();
                datamanager->updateUserFile();
                delete selectedVidID;
                selectedVidID = nullptr;
                
                
                cout<<string(30,'-')<<endl;
                cout<<"Like and dislike are reset"<<endl;
                cout<<string(30,'-')<<endl;
                break;}
            // for deleting a video
            else if (*choice =='c'){
                // get the video id
                string* selectedVidID = new string;
                cout<<"Enter the exact ID of which video would you like to delete"<<endl;
                cin>>* selectedVidID;
                // update the video- basically deletes from the main vector data
                datamanager->updateVideo(selectedVidID);
                // again update te set and map
                allVideos.clear();
                videos_and_ratios.clear();
                fillallVideos(datamanager);
                // update score
                float* sum = new float(0.0);
                *sum = this->calculateTotalRatio();
                this->setTotalRatio(*sum);
                delete sum;
                sum = nullptr;
                // update files
                datamanager->updateVideosFile();
                datamanager->updateUserFile();
                
                
                cout<<string(30,'-')<<endl;
                cout<<"The video "<<*selectedVidID<<" is deleted"<<endl;
                cout<<string(30,'-')<<endl;
                delete selectedVidID;
                selectedVidID = nullptr;
                break;}
            else if(*choice =='d'){  delete choice;choice = nullptr;delete vidSet;vidSet = nullptr;return;}
            else{cout<<"Invalid option! please re enter."<<endl;}
        }
        
        delete choice;
        choice = nullptr;
        delete vidSet;
        vidSet = nullptr;
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// prints informations of the creator
ostream& operator<<(ostream &str, Creator &s){
    string sentence = "Channel Name: "+s.getName()+"\n";
    str<<sentence<<endl;
    // print all the videos if exist
    try{
        str<<"Videos:"<<endl;
        // if there is no video throw noscoreexception
        if (s.videos_and_ratios.empty()) {
            throw NoScoreException("No videos available.");
        }
        // cout all the videos
        for(Video video: s.getAllVideos())
            cout<<video;
    // print the exception message
    }catch(NoScoreException nse){cout<<nse.what()<<endl;}
    
    return str;
}

// custom iterator, "typename" necessary to resolve nesting:
Creator::iterator::iterator(multimap<string, float>& map,
                               const typename multimap<string, float>::iterator& i)
    : r(&map), it(i) {}

// if equals
bool Creator::iterator::operator==(const iterator& x) const {
    return it == x.it;
}

// if not equals
bool Creator::iterator::operator!=(const iterator& x) const {
    return !(*this == x);
}

// pointer
std::pair<const string, float>& Creator::iterator::operator*() const {
    return *it;
}

// 1 addition
Creator::iterator& Creator::iterator::operator++() {
    ++it;
    if (it == r->end())
        it = r->begin();
    return *this;
}


Creator::iterator Creator::iterator::operator++(int) {
    iterator tmp = *this;
    ++*this;
    return tmp;
}

// 1 deletion
Creator::iterator& Creator::iterator::operator--() {
    if (it == r->begin())
        it = r->end();
    --it;
    return *this;
}


Creator::iterator Creator::iterator::operator--(int) {
    iterator tmp = *this;
    --*this;
    return tmp;
}
// inserting into the map
Creator::iterator Creator::iterator::insert(const pair<const string, float>& x) {
    return iterator(*r, r->insert(it, x));
}

// erasing from the map
Creator::iterator Creator::iterator::erase() {
    return iterator(*r, r->erase(it));
}

// reference to first
Creator::iterator Creator::begin() {
    return iterator(videos_and_ratios, videos_and_ratios.begin());
}

// reference to last
Creator::iterator Creator::end()
    {
       return iterator(videos_and_ratios, videos_and_ratios.end());
   }
// size of the map, size_t for better precision
size_t Creator::size(){return videos_and_ratios.size();}


