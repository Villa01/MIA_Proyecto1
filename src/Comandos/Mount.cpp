
#include "Mount.h"


Mount::Mount(vector<infoPart> *parts){
    this->parts = parts;
}

void Mount::agregarParametros(vector<Parametro> params){
    this->setParametros(params);
}

void Mount::assignParameters(){

    Algorithms a;

    if(this->getParams().size()<2)
    {
        Algorithms::printError("No hay suficientes parametros en el comando. ");
        exit(1);
    }

    vector<string> values = this->getParamsStringValues();
    vector<string> names = this->getParamsStringNames();

    int posPath = a.searchPosition("PATH", names);
    if(posPath==-1){
        Algorithms::printError("No se encontró el parametro path.");
        return;
    } else {
        this->setPath(values[posPath]);
    }

    int posName = a.searchPosition("NAME", names);
    if(posName == -1){
        Algorithms::printError("No se encontró el parametro name");
        exit(1);
    } else {
        this->setName(values[posName]);
    }
}

void Mount::mount(){
    // Obtener MBR
    Algorithms a;
    Mbr mbr = a.obtainMbr(this->getPath());

    // Obtener particiones primarias y extendidas
    vector<Partition> partitions = {mbr.mbr_partition1, mbr.mbr_partition2, mbr.mbr_partition3, mbr.mbr_partition4};
    vector<Partition> activePartitions;
    bool extended = false;
    for(Partition part : partitions){
        if(part.part_status == '1'){
            if(part.part_type=='E'){
                extended = true;
            }
            if(a.areEqual(part.part_name, this->getName())){
                activePartitions.push_back(part);
            }
        }
    }
    
    // Si hay particioens extendidas obtener las logicas
    Partition extended_part;
    vector<EBR> ebr_list;
    if(extended){
        for(Partition part : activePartitions){
            if(part.part_type=='E'){
                extended_part = part;
            }
        }

        ebr_list = a.obtain_ebr_list(extended_part, this->getPath());
    }


    int cont = this->obtainDiskNumber();
    string num = to_string(cont) ;
    char letra = this->obtainPartLetter();
    string id = "07" + num + letra;
    char ID[5];
    strcpy(ID,id.c_str());

    // Llenar un vector de informacion de las particiones
    for(Partition part : activePartitions){
        if(a.areEqual(part.part_name, this->getName())){
            infoPart ip;
            ip.path = this->getPath();
            strcpy(ip.part_name,part.part_name);
            strcpy(ip.part_id,ID);
            ip.part_size = part.part_size;
            ip.part_start = part.part_start;
            ip.letter = letra;
            ip.disk = cont;
            (this->parts)->push_back(ip);
            num = to_string(cont);
            letra = cont + 65;
            id = "07" + num + letra;
            strcpy(ID,id.c_str());
        }
        
    }

    if(ebr_list.size() > 0){
        for(EBR part : ebr_list){
            cout<<part.part_name<<endl;
            if(a.areEqual(part.part_name, this->getName())){
                infoPart ip;
                ip.path = this->getPath();
                strcpy(ip.part_name,part.part_name);
                strcpy(ip.part_id,ID);
                ip.part_size = part.part_size;
                ip.part_start = part.part_start;
                ip.disk = cont;
                ip.letter = letra;

                (this->parts)->push_back(ip);
                num = to_string(cont);
                id = "07" + num + letra;
                strcpy(ID,id.c_str());
            }
            
        }
    }

    Algorithms::printInfo("Particiones montadas");
    for(infoPart info : *(this->parts)){
        cout<<info.path<<" | "<<info.part_name<<" | "<<info.part_id<<endl;
        
    }

    // Crear una lista doble enlazada
}

int Mount::obtainDiskNumber(){
    int num;
    Algorithms a;
    if((this->parts)->size() < 1){
        num = 1;
    } else {
        bool discoExistente = false;
        vector<infoPart> parts = *(this->parts);
        int temp =1;
        for (size_t i = 0; i < parts.size(); i++)
        {       
                string partPath = parts[i].path;
                string nombreDisco = partPath.substr(partPath.find_last_of("/")+1, partPath.size());
                string partPath2 = this->getPath();
                string nombreDisco2 = partPath2.substr(partPath2.find_last_of("/")+1, partPath2.size());
            if(a.areEqual(nombreDisco,nombreDisco2)){
                discoExistente = true;
                num = parts[i].disk;
            }
            if(parts[i].disk > temp){
                temp = parts[i].disk;
            }
        }

        if(discoExistente){
            num = temp;
        } else {
            num = temp+1;
        }
        
    }

    return num;
}

char Mount::obtainPartLetter(){
    // Encontrar todas las particiones del mismo disco
    Algorithms a;
    vector<infoPart> parts = *(this->parts);
    vector<infoPart> partsSameDisk;
    for(infoPart info : parts){
        string partPath = info.path;
        string nombreDisco = partPath.substr(partPath.find_last_of("/")+1, partPath.size());
        string partPath2 = this->getPath();
        string nombreDisco2 = partPath2.substr(partPath2.find_last_of("/")+1, partPath2.size());
        if(a.areEqual(nombreDisco,nombreDisco2)){
            partsSameDisk.push_back(info);
            
        }
    }
    cout<<"Parts same disk"<<partsSameDisk.size()<<endl;
    return 65 + partsSameDisk.size();
}

void Mount::setPath(string path){
    this->path = path;
}

string Mount::getPath(){
    return this->path;
}

void Mount::setName(string name){
    this->name =name;
}

string Mount::getName(){
    return this->name;
}