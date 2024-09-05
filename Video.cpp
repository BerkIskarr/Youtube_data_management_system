//
//  Video.cpp
//  Cpp2nd
//
//  Created by Berk Iskar on 07/01/2024.
//

#include "Video.h"
// initalize all the attributes also calculate video score
Video::Video(string* video_id,string* video_name,string* video_duration,int* no_likes,int* no_dislikes,string* channel_name): video_id(new string(*video_id)),video_name(new string(*video_name)),video_duration(new string(*video_duration)),no_likes(new int(*no_likes)),no_dislikes(new int(*no_dislikes)),channel_name(new string(*channel_name)),video_score(new float(static_cast<float>(*no_likes) / static_cast<float>(*no_dislikes))){}

// free memory
Video::~Video(){
    
    video_id = nullptr;
    video_name = nullptr;
    video_duration = nullptr;
    no_likes = nullptr;
    no_dislikes = nullptr;
    channel_name = nullptr;
    
}

string* Video::getVideo_id() const{return this->video_id;}
string* Video::getVideo_name() const{return this->video_name;}
string* Video::getVideo_duration() const{return this->video_duration;}
int* Video::getNo_likes() const{return this->no_likes;}
int* Video::getNo_dislikes() const{return this->no_dislikes;}
string* Video::getChannelname() const{return this->channel_name;}
    float Video::getVideo_score() const{
        if(*this->no_dislikes>0){return (*this->no_likes/(*this->no_dislikes));}// calculates video score again
        else{ return 0; }
    }
    

void Video::Like(){(*this->no_likes)++;}// increase like
void Video::Dislike(){(*this->no_dislikes)++;}// increase dislike
void Video::setVideoScore(float* new_score){this->video_score = new_score;}
void Video::setName(string* name){
    *this->video_name = *name;// set name
}
void Video::setLike(int* like){
    *this->no_likes = *like;
}
void Video::setDislike(int* dislike){
    *this->no_dislikes = *dislike;
}
bool Video::operator<(const Video& other) const{
        return  other.getVideo_score()<this->getVideo_score();// need for sortin sets or other data types
    }
// print infos to stream
ostream& operator<<(ostream &out,const Video& video){
    return out<<*video.getVideo_id()<<","<<*video.getVideo_name()<<","<<*video.getVideo_duration()<<","<<*video.getNo_likes()<<","<<*video.getNo_dislikes()<<","<<*video.getChannelname()<<endl;
}



