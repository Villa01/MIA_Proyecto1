
using namespace std;

#include <string>
#include <vector>


#include "./parametro.h"

/*
* Parametros de cada comando. 
*/
/*
Parametro::Parametro(string nombre, string valor){
    this->setNombre(nombre);
    this->setValor(valor);
}
*/

Parametro::Parametro(){
    //printf("\e[0;36m---Creando un parametro\n");
}

void Parametro::setNombre(string nombre){
    //printf("\e[0;36m---\tEl nombre es: %s\n",nombre.c_str());
    this->nombre = nombre;
}

void Parametro::setValor(string valor){
    //printf("\e[0;36m---\tEl valor es: %s\n",valor.c_str());

    this->valor = valor;
}

string Parametro::getValor(){
    return this->valor;
}

string Parametro::getNombre(){
    return this->nombre;
}


