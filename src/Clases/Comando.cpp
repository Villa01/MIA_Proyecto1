

using namespace std;

#include "./Comando.h"

#include <vector>

Comando::Comando(){
    //printf("\e[0;36m---Creando un nuevo comando\n");
}

Comando::~Comando(){
}

void Comando::agregarParametros(vector<Parametro>params){
    this->setParametros(params);
}


void Comando::assignParameters(){
    //printf("Parametros del comando\n");
}


vector<string> Comando::getParamsStringNames(){
    vector<Parametro> params = this->getParams();
    vector<string> v;
    for (int i = params.size() - 1; i >= 0; i--)
    {
        string nombre = params[i].getNombre();
        v.push_back(nombre);
    }
    return v;   
}

vector<string> Comando::getParamsStringValues(){
    vector<Parametro> params = this->getParams();
    vector<string> v;
    for (int i = 0; i< params.size(); i++)
    {
    
        string nombre = params[i].getValor();
        v.push_back(nombre);
    }
    return v;   
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
