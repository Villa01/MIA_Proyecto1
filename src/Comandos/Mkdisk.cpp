

using namespace std;


#include "Mkdisk.h"

Mkdisk::Mkdisk() : Comando(){
    printf("\e[0;36m---INFO: Creando disco\n");
}

void Mkdisk::agregarParametros(vector<Parametro> params){
    //printf("\e[0;36m---Agregando parametros\n");
    this->setParametros(params);

}


void Mkdisk::assignParameters(){

    if(this->getParams().size()==0){
        std::cout <<"\e[0;31m"<< "--- ERROR: No hay suficientes parametros en el comando MKDISK" << std::endl;
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
        this->fit= "FF";
    } else {

        this->fit= a.toUpper(values[posF]);
    }

    // Asignar u 
    int posU = a.searchPosition("U", sparams);

    if (posU == -1){
        std::cout <<"\e[0;33m"<< "--- WARNING: no se incluyó el parametro U, se usará Megabytes por defecto" << std::endl;
        this->units = "M";
    } else {

        this->units= a.toUpper(values[posU]);
        
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

void Mkdisk::createDisk(){
    Algorithms a;
    string units = this->getUnits();
    int bufferSize = this->getSize();

    if (a.areEqual(units, "K")){
        bufferSize *= 1024;
    } else if(a.areEqual(units, "M")){
        bufferSize *= 1024*1024;
    } else { // Este error no deberia pasar nunca por el analisis léxico
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, el parametro U es incorrecto" << std::endl;
        return;
    }
    this->setSizeInBytes(bufferSize);
    char *buffer;

    buffer = (char*)malloc(bufferSize);


    cout<< bufferSize <<endl;
    // Llenando buffer

    for (int i = 0; i < bufferSize-1; i++)
    {
        buffer[i]='\0';
        //cout<<i<<endl;
    }
    
    // Abrir archivo

    FILE *file = fopen(this->getPath().c_str(),"wb");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", this->getPath().c_str());
        exit(1);
    }

    // Escribir en el disco


    for (int i = 0; i < bufferSize-1; i++)
    {
        fwrite(&buffer,1024,1,file );
    }

    fclose(file);


    this->asignarMbr();
    

}

void Mkdisk::asignarMbr(){
    Mbr mbr;
    Algorithms a;

    mbr.mbr_tamano = this->getSizeInBytes();
    strcpy(mbr.mbr_fecha_creacion, a.obtainDate().c_str());
    mbr.mbr_disk_signature = rand() %100;
    mbr.disk_fit = this->getFit()[0];

    // Particiones vacias
    Partition vacia;
    vacia.part_status='0';
    vacia.part_type='-';
    vacia.part_fit='-';
    vacia.part_start=-1;
    vacia.part_size=-1;
    vacia.part_name[0] = '\0';

    mbr.mbr_partition1 = vacia;
    mbr.mbr_partition2 = vacia;
    mbr.mbr_partition3 = vacia;
    mbr.mbr_partition4 = vacia;

    FILE *file = fopen(this->getPath().c_str(), "rb+");

    if(file != NULL){
        fseek(file,0,SEEK_SET );
        fwrite(&mbr, sizeof(mbr), 1, file);
        fclose(file);
        printf("\x1B[32m--- INFO: Se le asignó el MBR al disco %d con el tamaño %d en la fecha %s y ajuste %d\n", mbr.mbr_disk_signature, mbr.mbr_tamano, mbr.mbr_fecha_creacion, mbr.disk_fit);
    } else {
        printf("\e[0;31m--- ERROR: No se pudo crear el MBR");
    }
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

void Mkdisk::setSizeInBytes(int sizeInBytes){
    this->sizeInBytes = sizeInBytes;
}

int Mkdisk::getSizeInBytes(){
    return this->sizeInBytes;
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