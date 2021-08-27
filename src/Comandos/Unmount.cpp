
#include "Unmount.h"


Unmount::Unmount(vector<infoPart> *parts){
    this->parts = parts;
}

void Unmount::agregarParametros(vector<Parametro> params){
    this->setParametros(params);
}

void Unmount::assignParameters(){

    Algorithms a;

    if(this->getParams().size()<1)
    {
        Algorithms::printError("No hay suficientes parametros en el comando. ");
        exit(1);
    }

    vector<string> values = this->getParamsStringValues();
    vector<string> names = this->getParamsStringNames();

    int posId = a.searchPosition("ID", names);
    if(posId==-1){
        Algorithms::printError("No se encontró el parametro id.");
        return;
    } else {
        this->setId(values[posId]);
    }
}

void Unmount::unmount(){

    Algorithms a;
    bool unmounted = false;
    for (int i =0; i< this->parts->size();i++)
    {
        if(a.areEqual((*(this->parts))[i].part_id, this->getId())){
            this->parts->erase(next(this->parts->begin() + i -1));
            Algorithms::printInfo("Particion " + this->getId() + " desmontada.");
            unmounted = true;
        }
    }

    if(!unmounted){
        Algorithms::printInfo("No se desmontó " + this->getId());
    }
    
    
    for(infoPart info : *(this->parts)){
        cout<<info.path<<" | "<<info.part_name<<" | "<<info.part_id<<endl;
    }

}


void Unmount::setId(string id){
    this->id =id;
}

string Unmount::getId(){
    return this->id;
}