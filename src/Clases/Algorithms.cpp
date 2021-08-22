

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

Mbr Algorithms::obtainMbr(string path){
    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", path.c_str());
        exit(1);
    }

    fseek(file, 0, SEEK_SET);

    Mbr mbr;

    fread(&mbr, sizeof(mbr), 1, file);
    fclose(file);
    return mbr;
}

vector<EBR> Algorithms::obtain_ebr_list(Partition extended,string path){
    vector<EBR> ebr_list;

    int start_position = extended.part_start;
    while(start_position != -1){

        EBR ebr = this->obtain_ebr(start_position, path);
        ebr_list.push_back(ebr);

        start_position = ebr.part_start;
        
    }


    return ebr_list;
}

EBR Algorithms::obtain_ebr(int start_postion, string path){
    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", path.c_str());
        exit(1);
    }

    fseek(file, start_postion, SEEK_SET);

    EBR ebr;

    fread(&ebr, sizeof(ebr), 1, file);
    fclose(file);
    return ebr;
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