

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
    Algorithms a;

    cout<<this->getId()<<endl;
    cout<<this->getFs()<<endl;
    cout<<this->getType()<<endl;

    // Encontrar la informacion de la particion
    vector<infoPart> parts = *(this->getInfoParts());
    infoPart seleccionada;

    for(infoPart inf: parts){

        if(a.areEqual(inf.part_id, this->getId())){
            seleccionada = inf;
        }
    }

    if(a.areEqual(seleccionada.part_id, '\0\0\0\0\0') ){
        Algorithms::printError("No se encontró el ID. ");
        exit(0);
    }

    // Si es un formateo completo se llena de ceros

    if(a.areEqual(this->getFs(), "3FS")){
        Algorithms::fillWithZeros(seleccionada.part_start, seleccionada.part_size, seleccionada.path);
    }

        // Calcular numero de inodos
    int numInodos;
    if(a.areEqual(this->getFs(), "3FS")){
        float n = (seleccionada.part_size - sizeof(SuperBloque) -100*sizeof(Journal))/(4 + sizeof(INodo) + 3*sizeof(BloqueArchivos));
        numInodos = floor(n);
    } else if(a.areEqual(this->getFs(), "2FS")){
        float n = (seleccionada.part_size - sizeof(SuperBloque))/(4 + sizeof(INodo) + 3*sizeof(BloqueArchivos));
        numInodos = floor(n);
    } else {
        Algorithms::printError("No existe el formateo seleccionado. ");
        exit(0);
    }


    // Crear superbloque

    SuperBloque superBloque;
    superBloque.s_filesystem_type = 3;
    superBloque.s_inodes_count = numInodos;
    superBloque.s_blocks_count = 3*numInodos;
    superBloque.s_free_blocks_count = 3*numInodos;
    strcpy(superBloque.s_mtime,a.obtainDate().c_str());
    strcpy(superBloque.s_umtime, "00/00/0000 00:00:00");
    superBloque.s_mnt_count = 1;
    superBloque.s_magic = 0xEF53;
    superBloque.s_inode_size = sizeof(INodo);
    superBloque.s_block_size = sizeof(BloqueArchivos);
    superBloque.s_first_ino = 2;
    superBloque.s_first_blo = 2;
    superBloque.s_bm_inode_start=seleccionada.part_start + sizeof(SuperBloque) + (numInodos*sizeof(Journal)); 
    superBloque.s_bm_block_start=superBloque.s_bm_inode_start + numInodos ;
    superBloque.s_inode_start=superBloque.s_bm_block_start+3*numInodos;
    superBloque.s_block_start=superBloque.s_inode_start+numInodos*sizeof(INodo);

    // Escribir superbloque

    FILE * file;
    file=fopen(seleccionada.path.c_str(),"rb+"); //lectura y escritura de binario
    if(file==NULL){
        a.printError("No se pudo escribir el superbloque");
        exit(1);
    }

    fseek(file, seleccionada.part_start, SEEK_SET);
    fwrite(&superBloque, sizeof(superBloque), 1, file);
    
    // Escribir bitmaps
    char bmInodos[numInodos];
    char bmBloques[3*numInodos];

    // Conseguir el inicio dependiendo del sistema de archivos
    int inicioInodos;

    if(a.areEqual(this->getFs(), "3FS")){
        inicioInodos = seleccionada.part_start + sizeof(SuperBloque) + 100*sizeof(Journal);
    } else if(a.areEqual(this->getFs(), "2FS")){
        inicioInodos = seleccionada.part_start + sizeof(SuperBloque);
    }


    // Se llena el bitmap de inodos y bloques
    for(int i=0;i<numInodos;i++){
        bmInodos[i]='0'; 
        bmBloques[i]='0';
    }

    // Escritura de carpeta root

    bmBloques[0]= '1';
    bmBloques[1]= '2';

    fseek(file,iniciobloques, SEEK_SET);
    fwrite(&bibloques,sizeof(bibloques),1,arch);
    // formateo ext2

    // formateo ext3
}

void Mkfs::ext2_format(){

    // Calcular numero de bloques

    // Llenar bitmap de inodos

    // Llenar bitmap de bloques

    // Escribir los inodos

    // Escribir los bloques
}


void Mkfs::ext3_format(){
    // Calcular numero de inodos

    // Calcular numero de bloques

    // Llenar bitmap de inodos

    // Llenar bitmap de bloques

    // Escribir los inodos

    // Escribir los bloques
}