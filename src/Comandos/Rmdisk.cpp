

#include "Rmdisk.h"

Rmdisk::Rmdisk(){

}

void Rmdisk::assignParameters(){
    if(this->getParams().size()==0){
        std::cout <<"\e[0;31m"<< "--- ERROR: No hay suficientes parametros en el comando MKDISK" << std::endl;
    }

    Algorithms a;
    vector<string> sparams = this->getParamsStringNames();
    vector<string> values = this->getParamsStringValues();


    // Asignar path
    int posP = a.searchPosition("PATH", sparams);

    if (posP == -1){
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, agregue el parametro path" << std::endl;
        return;
    } else {
        this->path= values[posP];
    }
}

void Rmdisk::agregarParametros(vector<Parametro> params){
    this->setParametros(params);
}

void Rmdisk:: deleteDisk(){
    std::cout <<"\e[0;33m"<< "--- WARNING: ¿Está segur@ que desea eliminar al disco " << this->getPath()<< "? 1. Si 0. No\e[0;37m"<< std::endl;

    char confirm[1];
    cin>>confirm;
    int val = (int)confirm[0];
    int succesful;

    if ( val == 49){
        succesful = remove(this->getPath().c_str());

        if ( succesful = 0) {
            printf("\e[0;36m---INFO: Se eliminó el disco\n");
        } else {
            std::cout <<"\e[0;31m"<< "--- ERROR: No se pudo eliminar el disco " << std::endl;
        }
    }
    else if (val == 48) {
        printf("\e[0;36m---INFO: No se ha eliminado el disco \n");
    } else {
        std::cout <<"\e[0;31m"<< "--- ERROR: Valor inválido " << std::endl;
    }

}

void Rmdisk::setPath(string s){
    this->path = s;
}

string Rmdisk::getPath(){
    return this->path;
}