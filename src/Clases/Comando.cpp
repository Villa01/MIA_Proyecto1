

using namespace std;

#include "./Comando.h"

#include <vector>

Comando::Comando(){
    printf("Creando un nuevo comando\n");
}

Comando::~Comando(){
    printf("Creando un parametro\n");
}

void Comando::agregarParametros(vector<Parametro>params){
    this->setParametros(params);
}


void Comando::assignParameters(){
    printf("Parametros del comando");
}

// Setters & getters

string Comando::getNombre(){
    return this->nombre;
}

vector<Parametro> Comando:: getParams(){
    return this->params;
}

void Comando::setNombre(string nombre){
    this->nombre = nombre;
}

void Comando::setParametros(vector<Parametro> params){
    this->params = params;
}
