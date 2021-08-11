

#include "Algorithms.h"


Algorithms::Algorithms(){

}

int Algorithms::searchPosition(string s, vector<string> v){


    for (int i = v.size() - 1; i >= 0; i--)
    {
        if(this->areEqual(this->toUpper(s), this->toUpper(v[i]))){
            return v.size()-1-i;
        }
    }

    return -1;
}

string Algorithms::toUpper(string s){
    string sUpper = s;
    std::transform(sUpper.begin(), sUpper.end(),sUpper.begin(), ::toupper);
    return sUpper;
}

bool Algorithms::areEqual(string s, string d){
    if(strcmp(s.c_str(),d.c_str())==0){
        return true;
    }
    return false;
    
}

string Algorithms::obtainDate(){
    time_t time = std::time(0);
    tm* now = localtime(&time);
    return  to_string(now->tm_mday) + "/" +
                   to_string(now->tm_mon) + "/" +
                   to_string(now->tm_mday) + " " +
                   to_string(now->tm_hour) + ":" +
                   to_string(now->tm_min) + ":" + 
                   to_string(now->tm_sec);

}