
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

    int cont = (this->parts)->size();
    string num = to_string(cont+ 1) ;
    char letra = cont + 65;
    string id = "07" + num + letra;
    char ID[5];
    strcpy(ID,id.c_str());

    // Llenar un vector de informacion de las particiones
    for(Partition part : activePartitions){
        infoPart ip;
        ip.path = this->getPath();
        strcpy(ip.part_name,part.part_name);
        strcpy(ip.part_id,ID);
        ip.part_size = part.part_size;
        ip.part_start = part.part_start;
        (this->parts)->push_back(ip);
        cont++;

        num = to_string(cont);
        letra = cont + 65;
        id = "07" + num + letra;
        strcpy(ID,id.c_str());
    }

    if(ebr_list.size() > 0){
        for(EBR part : ebr_list){
            infoPart ip;
            ip.path = this->getPath();
            strcpy(ip.part_name,part.part_name);
            strcpy(ip.part_id,ID);
            ip.part_size = part.part_size;
            ip.part_start = part.part_start;

            (this->parts)->push_back(ip);
            cont++;
            num = to_string(cont);
            letra = cont + 65;
            id = "07" + num + letra;
            strcpy(ID,id.c_str());
        }
    }

    Algorithms::printInfo("Particiones montadas");
    for(infoPart info : *(this->parts)){
        cout<<info.path<<" | "<<info.part_name<<" | "<<info.part_id<<endl;
        
    }

    // Crear una lista doble enlazada
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