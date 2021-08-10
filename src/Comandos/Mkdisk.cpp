

using namespace std;


#include "Mkdisk.h"

Mkdisk::Mkdisk() : Comando(){
    printf("\e[0;36m---Creando disco\n");
}

void Mkdisk::agregarParametros(vector<Parametro> params){
    printf("\e[0;36m---Agregando parametros\n");
    this->setParametros(params);

}


void Mkdisk::assignParameters(){

    if(this->getParams().size()==0){
        std::cout <<"\e[0;31m"<< "-- No hay suficientes parametros en el comando MKDISK" << std::endl;
    }

    // Buscar Size
    Algorithms a;
    int i = a.searchPosition("SIZE", this->getParamsString());
}

vector<string> Mkdisk::getParamsString(){
    vector<Parametro> params =this->getParams();
    vector<string> v[params.size()];
    for (int i = params.size() - 1; i >= 0; i--)
    {
        string nombre = params[i].getNombre();
       
    }
    
}

// Setters & getters

void Mkdisk::setSize(float size){
    this->size = size;
}

float Mkdisk::getSize(){
    return this->size;
}

void Mkdisk::setPath(string path){
    this->path = path;
}

string Mkdisk::getPath(){
    return this->path;
}

void Mkdisk::setUnits(string units){
    this->units = units;
}

string Mkdisk::getUnits(){
    return this->units;
}

void Mkdisk::setFit(string fit){
    this->fit = fit;
}

string Mkdisk::getFit(){
    return this->fit;
}