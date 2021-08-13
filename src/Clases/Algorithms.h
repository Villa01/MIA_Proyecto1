

#ifndef ALGORITHMS
#define ALGORITHMS
using namespace std;

#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <ctime>
#include <iostream>


class Algorithms {


    public:
        Algorithms();
        int searchPosition(string s, vector<string>v);
        string toUpper(string s);
        bool areEqual(string, string);
        string obtainDate();
};

#endif