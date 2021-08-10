

#include "Algorithms.h"


Algorithms::Algorithms(){

}

int Algorithms::searchPosition(string s, vector<string> v){

    for (int i = v.size() - 1; i >= 0; i--)
    {
        if(strcmp(s.c_str(),v[i].c_str())==0){
            return i;
        }
    }

    return -1;
    
}