//
//  Video.h
//  Cpp2nd
//
//  Created by Berk Iskar on 07/01/2024.
//

#ifndef Video_h
#define Video_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <random>
using namespace std;
// Video object for storing each line in the youtube data file
class Video{
private:
    string* video_id;
    string* video_name;
    string* video_duration;
    int* no_likes;
    int* no_dislikes;
    string* channel_name;
    float* video_score;// score of the video
public:
    // constructor to initialize all the attributes
    Video(string* video_id,string* video_name,string* video_duration,int* no_likes,int* no_dislikes,string* channel_name);

    ~Video();// deconstructo for freeing pointers
    string* getVideo_id() const;
    string* getVideo_name() const;
    string* getVideo_duration() const;
    int* getNo_likes() const;
    int* getNo_dislikes() const;
    string* getChannelname() const;
    float getVideo_score() const;// returns video score
    
    void Like();// increase no of likes 1
    void Dislike();// increase no of likes 1
    void setVideoScore(float*); // update video score
    void setName(string* name); // update name
    void setLike(int* like); // update like
    void setDislike(int* dislike); // update dislike
    bool operator<(const Video& other) const; // for sorting desc according to its score
    friend ostream& operator<<(ostream &out,const Video& video); // printing video infos
};



#endif /* Video_h */
