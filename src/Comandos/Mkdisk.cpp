

using namespace std;

#include <string>
#include <vector>

#include "Mkdisk.h"

Mkdisk::Mkdisk() : Comando(){
    printf("Creando disco\n");
}

void Mkdisk::agregarParametros(vector<Parametro> params){
    printf("Agregando parametros\n");
    this->setParametros(params);

    string nombre = this->getNombre();
    
    printf("%s\n",nombre.c_str());

    printf("%s\n",params[0].getNombre().c_str());
}


void Mkdisk::assignParameters(){
    
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