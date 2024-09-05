//
//  User.cpp
//  Cpp2nd
//
//  Created by Berk Iskar on 04/01/2024.
//

#include "User.h"
#include "Creator.h"
// constructo score is  initialized empty
User::User(const string &name, int regNo): Person(name), regNo(regNo),score(){}

int User::getRegNo() const{return this->regNo;}// returns regno
// main display of suer
void User::showMenu(DataManager* datamanager){
    try{
        int* choice = new int; // to save which option was chosen
        cout<<string(30,'-')<<endl;
        cout<<"Welcome "<< getName()<<"!"<<endl;
        // loop till user exists
        while(true){
            cout<<string(30,'-')<<endl;
            cout<<"\nWhat can I do for you?\n"<<endl;
            cout<<"1- Get Video"<<endl;
            cout<<"2- Get Video Recommendations"<<endl;
            cout<<"3- Trending Channels"<<endl;
            cout<<"4- Exit"<<endl;
            cout<<string(30,'-')<<endl;
            cin>>*choice;
            // if datatype besides int inputted, restart
            if (cin.fail()) {
                cerr << "Invalid input! Please enter integer." << endl;
                cerr<<"Restarting..."<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                delete choice;
                choice = nullptr;return;}
            cout<<string(30,'-')<<endl;
            // gets videos according to the entered keyword
            if(*choice==1){
                getVideo(datamanager);
            }
            // gets video recommendation according to their scores
            else if (*choice==2){
                getVideoRecommendations(datamanager);
            }
            // displays trending channels and their videos
            else if (*choice==3){
                displayTrendingChannels(datamanager);
            }
            // exists
            else if (*choice==4){delete choice;
                choice = nullptr;cout<<"Hope to see you again, bye!"<<endl;cout<<string(30,'-')<<endl;return;}
            // invalid option
            else{cout<<"Invalid option! Re enter"<<endl;}
        }}catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
 
}
// returns the type, need this to be able to discriminate person objects in data, if get type is user, means that our person referenced object is created as user
PersonType User::getType() const {
        return PersonType::User;
    }
// In here used only unique_ptr, returns keyword and transforms into only first letter upper
unique_ptr<string> User::getKeyword(){
    unique_ptr<string>(keyword) = make_unique<string>();
    cout<<string(30,'-')<<endl;
    cout<<"Enter a 'Keyword' to search!"<<endl;
    cin>>*keyword;
    if (cin.fail()) {
        cerr << "Invalid input! Please enter integer." << endl;
        cerr<<"Restarting..."<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');terminate();}
    cout<<string(30,'-')<<endl;
    // again transform the format as only first letter being uppercase
    transform(keyword->begin(), keyword->end(), keyword->begin(), ::tolower);
    if (!keyword->empty())(*keyword)[0] = ::toupper((*keyword)[0]);
    return keyword;}

// In here used only unique_ptr, returns random videos if includes the keyword in either video name or channel name
// copied the vector data, because i dont wanna shuffle the actual data- used shuffle because in the descriptions was saying we need to get videos randomly.
void User::getVideo(DataManager* datamanager){
    try{
        unique_ptr<string>(keyword) =getKeyword();
        unique_ptr<queue<Video>> VideoQueue = make_unique<queue<Video>>();
        // copy actual data
        vector<Video> shuffledVideos = datamanager->getVideos();
        random_device rd;
        mt19937 mt(rd());
        // randomize the copied vector
        shuffle(shuffledVideos.begin(), shuffledVideos.end(), mt);
        // check all the videos if the entered keyword exists
        for (Video& video:shuffledVideos) {
            size_t foundName = video.getVideo_name()->find(*keyword);
            size_t foundChannel = video.getChannelname()->find(*keyword);
            // if keyword found in channel or video name add into the queue
            if (foundName != string::npos || foundChannel != string::npos) {
                VideoQueue->push(video);
                
            }
            // limit size into 20
            if(VideoQueue->size()>=20)break;
        }
        
        cout<<string(30,'-')<<endl;
        // if queue is not empty print all the videos inside
        while(!VideoQueue->empty()){
            cout << VideoQueue->front();
            VideoQueue->pop();}
        
        cout<<string(30,'-')<<endl;
        // function to update like and dislike
        ask_video_update_likedis(datamanager);
        // update files
        datamanager->updateVideosFile();
        datamanager->updateUserFile();
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
// Ask the user for a keyword and then display top 10 videos based on their like/dislike ratio
void User::getVideoRecommendations(DataManager* datamanager){
    try{
        // get the keyword
        unique_ptr<string>(keyword) =getKeyword();
        // list pointer to save the top 10 videos
        list<Video>* recommended_videos = new list<Video>;
        // check all the videos if the entered keyword exists
        for (Video& video:datamanager->getVideos()) {
            size_t foundName = video.getVideo_name()->find(*keyword);
            size_t foundChannel = video.getChannelname()->find(*keyword);
            // if keyword found in channel or video name add into the list
            if (foundName != string::npos || foundChannel != string::npos) {
                recommended_videos->emplace_back(video);
            }
        }
        // sort the list according to the scores
        recommended_videos->sort([](const Video& vid1, const Video& vid2) {
            return vid1.getVideo_score() > vid2.getVideo_score();
        });
        
        // copy the list but only add top 10 videos
        list<Video>* recommended_ten_videos = new list<Video>(recommended_videos->begin(), std::next(recommended_videos->begin(), 10));
        delete recommended_videos;
        recommended_videos = nullptr;
        // print the videos
        cout<<string(30,'-')<<endl;
        for(Video& video:*recommended_ten_videos)
            cout<<video;
        
        // update like dislike of the video
        ask_video_update_likedis(datamanager);
        // update files
        datamanager->updateVideosFile();
        datamanager->updateUserFile();
        
        delete recommended_ten_videos;
        recommended_ten_videos = nullptr;
    }catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}

// ask the video and then update that video's like and dislike
void User::ask_video_update_likedis(DataManager* datamanager){
    try{
        unique_ptr<int>(choice1) = make_unique<int>();
        cout<<string(30,'-')<<endl;
        // either get video or return menu
        cout<<"1-> Get Video\n2-> Return Main Menu"<<endl;
        cin>>*choice1;
        if (cin.fail()) {
            cerr << "Invalid input! Please enter integer." << endl;
            cerr<<"Restarting..."<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');return;}
        cout<<string(30,'-')<<endl;
        unique_ptr<string> selectedVid;
        unique_ptr<string> likedordisliked;
        
        switch (*choice1) {
            case 1:
                selectedVid = make_unique<string>();
                // define which video wanted
                while(true){
                    cout<< "Which video do you want to get?(Enter video ID exactly)"<<endl;
                    cin>> *selectedVid;
                    if (cin.fail()) {
                        cerr << "Invalid input! Please enter string." << endl;
                        cerr<<"Restarting..."<<endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');return;}
                    // search through the data vector since the video itself needs to be updated
                    for(Video& video: datamanager->getVideos()){
                        if(*video.getVideo_id()==*selectedVid){
                            likedordisliked = make_unique<string>();
                            cout<<video<<endl;
                            do{
                                cout<<string(30,'-')<<endl;
                                // liked or disliked?
                                cout<<"Like or Dislike?\n(type 'like' for like, 'dislike' for dislike)"<<endl;
                                cin>>*likedordisliked;
                                if (cin.fail()) {
                                    cerr << "Invalid input! Please enter string." << endl;
                                    cerr<<"Restarting..."<<endl;
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');return;}
                                cout<<string(30,'-')<<endl;
                                // check if valid string entered, if not ask again
                            }while(*likedordisliked!="like" && *likedordisliked!="dislike");
                            // update all the data
                            datamanager->updateLike_or_Dislike(video, std::move(likedordisliked));
                            datamanager->updateVideosFile();
                            datamanager->updateUserFile();
                            break;}
                    }
                    // return main menu
                case 2:
                    return;
                default:
                    cout<<"Invail choice! Please re enter."<<endl;}
        }}catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}

// func to display top trending channels according to their channel scores and then show their videos
void User::displayTrendingChannels(DataManager* datamanager){
    try{
        // pair because make it easier for user to find the specific channel, and channel can directly be accessed if int value is what user entered
        deque<pair<int,Creator>>(trendchannels);
        int x=1;
        // search through the users data
        for (Person* person : datamanager->getUsers()) {
            float* sum = new float(0.0);
            Creator* creator = dynamic_cast<Creator*>(person);
            // if dynamic cast successful
            if (creator) {
                // fill multimap and set in creator class
                creator->fillallVideos(datamanager);
                // save the total score
                *sum = creator->calculateTotalRatio();// use of only iterator or with accumulate
                creator->setTotalRatio(*sum);
                // add into deque
                trendchannels.push_back({x,*creator});
                // also add into the map
                this->score.insert({creator->getRegNo(),{creator->getChannelName(),*sum}});
                x++;
            }
            delete sum;
            sum = nullptr;
        }
        // sort deque desc
        sort(trendchannels.begin(), trendchannels.end(),[]( auto& a, auto& b) {
            return a.second.getTotalRatio() > b.second.getTotalRatio();
        });
        // limit size to 10
        if (trendchannels.size() > 10) {
            trendchannels.erase(trendchannels.begin() + 10, trendchannels.end());
        }
        if(!trendchannels.empty()){
            cout<<string(30,'-')<<endl;
            // display channels to the user
            for (auto& creator : trendchannels) {
                cout<<creator.first<<"- Channel Name: "<<creator.second.getName()<<", Channel Score: "<<creator.second.getTotalRatio()<<endl;
            }cout<<string(30,'-')<<endl;
            int* choice = new int;
            cout<< "Which channel do you wanna explore (Enter the corresponding number)?"<<endl;
            cin>>*choice;
            if (cin.fail()) {
                cerr << "Invalid input! Please enter an integer." << endl;
                cerr<<"Restarting..."<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');return;}
            // if the correct number entered show all the videos
            for(auto& creator : trendchannels){
                if(creator.first==*choice){
                    cout<<creator.second;
                }
            }cout<<string(30,'-')<<endl;
            // update data
            ask_video_update_likedis(datamanager);
            datamanager->updateVideosFile();
            datamanager->updateUserFile();
            delete choice;
            choice = nullptr;
        }}catch(...){cout<<"Something's wrong! Terminating..."<<endl;return;}
}
