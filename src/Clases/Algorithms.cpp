

#include "Algorithms.h"


int Algorithms::searchPosition(string s, vector<string> v){

    for (int i = v.size() - 1; i >= 0; i--)
    {
        if(s.compare(v[i])){
            printf("%s es igual a %s", s.c_str(), v[i].c_str());
            return i;
        }
    }

    return -1;
    
}