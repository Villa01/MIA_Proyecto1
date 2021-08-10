

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



    Algorithms a;
    vector<string> sparams = this->getParamsStringNames();
    vector<string> values = this->getParamsStringValues();

    // Asignar Size
    int posSize = a.searchPosition("SIZE", sparams);
    if(posSize==-1){
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, agregue el parametro size" << std::endl;
        return;
    } else {
        
        this->setSize(stof(values[posSize]));
    }


    //  Asignar F
    int posF = a.searchPosition("F", sparams);

    if (posF == -1){
        std::cout <<"\e[0;33m"<< "--- WARNING: no se incluyó el parametro F, se usará el FF por defecto" << std::endl;
    } else {

        this->fit= values[posF];
    }

    // Asignar u 
    int posU = a.searchPosition("U", sparams);

    if (posU == -1){
        std::cout <<"\e[0;33m"<< "--- WARNING: no se incluyó el parametro U, se usará Megabytes por defecto" << std::endl;
    } else {

        this->units= values[posU];
    }

    // Asignar path
    int posP = a.searchPosition("PATH", sparams);

    if (posP == -1){
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, agregue el parametro path" << std::endl;
        return;
    } else {
        this->path= values[posP];
    }
}

vector<string> Mkdisk::getParamsStringNames(){
    vector<Parametro> params = this->getParams();
    vector<string> v;
    for (int i = params.size() - 1; i >= 0; i--)
    {
        string nombre = params[i].getNombre();
        v.push_back(nombre);
    }
    return v;   
}

vector<string> Mkdisk::getParamsStringValues(){
    vector<Parametro> params = this->getParams();
    vector<string> v;
    for (int i = 0; i< params.size(); i++)
    {
    
        string nombre = params[i].getValor();
        printf("%s\n", nombre.c_str());
        v.push_back(nombre);
    }
    return v;   
}


void Mkdisk::showInfo(){

    printf("\x1B[32m--- INFO: El disco está alojado en %s, tiene un tamaño de %.2f %s y se asigna por medio del %s\n",
            this->getPath().c_str(),
            this->getSize(),
            this->getUnits().c_str(),
            this->getFit().c_str());
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