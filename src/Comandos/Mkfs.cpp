

#include "Mkfs.h"


Mkfs::Mkfs(vector<infoPart> *infoParts):Comando(){
    this->setInfoParts(infoParts);
}

void Mkfs::agregarParametros(vector<Parametro> params){
    this->setParametros(params);
}

void Mkfs::assignParameters(){
    Algorithms a;

    vector<string> names = this->getParamsStringNames();
    vector<string> values = this->getParamsStringValues();


    int posId = a.searchPosition("ID", names);

    if (posId == -1){
        a.printError("Por favor, agregue el parametro id");
        exit(1);
    } else {
        this->setId(a.toUpper(values[posId]));
    }

    int posType = a.searchPosition("TYPE", names);

    if(posType == -1){  
        a.printWarning("No se incluyó el parametro type, se usará FULL por defecto.");
        this->setType("FULL");
    } else {
        this->setType(a.toUpper(values[posType]));
    }

    int posFs = a.searchPosition("FS", names);

    if(posFs == -1){
        a.printWarning("No se incluyó el parametro fs, se usará 2FS por defecto.");
        this->setFs("2FS");
    } else {
        this->setFs(a.toUpper(values[posFs]));
    }
    
}

void Mkfs::format(){
    cout<<this->getId()<<endl;
    cout<<this->getFs()<<endl;
    cout<<this->getType()<<endl;
}