

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

    fread(&mbr, sizeof(Mbr), 1, file);
    fclose(file);
    return mbr;
}

void Algorithms::writeMbr(Mbr mbr, string path){
    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudos escribir el mbr");
        exit(1);
    }

    fseek(file, 0, SEEK_SET);

    fwrite(&mbr, sizeof(Mbr), 1, file);
    fclose(file);
}

vector<EBR> Algorithms::obtain_ebr_list(Partition extended,string path){
    vector<EBR> ebr_list;

    int start_position = extended.part_start;
    while(start_position != -1){

        EBR ebr = this->obtain_ebr(start_position, path);
        if(ebr.part_status == '1'){
            start_position = ebr.part_next;
            ebr_list.push_back(ebr);
        } else {
            break;
        }
    }


    return ebr_list;
}

void Algorithms::showMbrInfo(string path){
    Mbr mbr = this->obtainMbr(path);

    printf("\x1B[32m--- INFO: Resumen MBR\n");
    cout<<"mbr_disk_signature: "<<mbr.mbr_disk_signature<<endl;
    cout<<"mbr_fecha_creacion: "<<mbr.mbr_fecha_creacion<<endl;
    cout<<"disk_fit: "<<mbr.disk_fit<<endl;
    cout<<"mbr_tamano: "<<mbr.mbr_tamano<<endl;

    vector<Partition> partitions{mbr.mbr_partition1, mbr.mbr_partition2, mbr.mbr_partition3, mbr.mbr_partition4};
    this->printPartitions(partitions, path);
}


void Algorithms::printPartitions(vector<Partition> partitions, string path){
    cout<<"\x1B[32m--- INFO: Info particiones"<<endl;
    for(Partition partition : partitions){
        if(partition.part_status == '1'){
            this->printPartition(partition, path);
        }
    }
}

void Algorithms::printPartition(Partition partition, string path){
    string s(1,partition.part_type);
    cout<<"part_name: "<<partition.part_name<<endl;
    cout<<"part_size: "<<partition.part_size<<endl;
    cout<<"part_start: "<<partition.part_start<<endl;
    cout<<"part_fit: "<<partition.part_fit<<endl;
    cout<<"part_type: "<<partition.part_type<<endl;
    if(this->areEqual(s, "E")){
        vector<EBR> ebr_list = this->obtain_ebr_list(partition, path);
    }

    cout<<endl;
}

void Algorithms::print_ebr_list(vector<EBR> ebr_list){
    cout<<endl;
    cout<<"\x1B[32m--- INFO: Info particiones logicas"<<endl;
    for(EBR ebr: ebr_list){
        if(ebr.part_status == '1'){
            this->print_ebr(ebr);
        }
    }
    cout<<endl;
}

void Algorithms::print_ebr(EBR partition){
    cout<<endl;
    cout<<"part_name: "<<partition.part_name<<endl;
    cout<<"part_size: "<<partition.part_size<<endl;
    cout<<"part_start: "<<partition.part_start<<endl;
    cout<<"part_fit: "<<partition.part_fit<<endl;
    cout<<"part_next: "<<partition.part_next<<endl;
    cout<<"part_status: "<<partition.part_status<<endl;
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