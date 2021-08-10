

#include "Algorithms.h"


Algorithms::Algorithms(){

}

int Algorithms::searchPosition(string s, vector<string> v){


    for (int i = v.size() - 1; i >= 0; i--)
    {
        std::transform(s.begin(), s.end(),s.begin(), ::toupper);
        std::transform(v[i].begin(), v[i].end(),v[i].begin(), ::toupper);

        if(strcmp(s.c_str(),v[i].c_str())==0){
            return v.size()-1-i;
        }
    }

    return -1;
}