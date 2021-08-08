
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
    printf("Creando un parametro\n");
}

void Parametro::setNombre(string nombre){
    this->nombre = nombre;
}

void Parametro::setValor(string valor){
    this->valor = valor;
}

string Parametro::getValor(){
    return this->valor;
}

string Parametro::getNombre(){
    return this->nombre;
}


