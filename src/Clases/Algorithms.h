

#ifndef ALGORITHMS
#define ALGORITHMS
using namespace std;

#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include "Estructuras.h"


class Algorithms {


    public:
        Algorithms();
        int searchPosition(string s, vector<string>v);
        string toUpper(string s);
        bool areEqual(string, string);
        string obtainDate();
        Mbr obtainMbr(string path);
        vector<EBR> obtain_ebr_list(Partition, string);
        EBR obtain_ebr(int, string);
};

#endif