

#include "Mkfs.h"


Mkfs::Mkfs(vector<infoPart> *infoParts):Comando(){
    this->setInfoParts(infoParts);
    Algorithms a;
    a.printInfo("Formateo de particiones");
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
        this->setId(values[posId]);
    }

    int posType = a.searchPosition("TYPE", names);

    if(posType == -1){  
        a.printWarning("No se incluyó el parametro type, se usará FULL por defecto.");
        this->setType("FULL");
    } else {
        this->setType(values[posType]);
    }

    int posFs = a.searchPosition("FS", names);

    if(posFs == -1){
        a.printWarning("No se incluyó el parametro fs, se usará 2FS por defecto.");
        this->setFs("2FS");
    } else {
        this->setFs(a.toUpper(values[posFs]));
    }
    
}

//EXEC -path = /home/erick/Clases/Archivos/Laboratorio/Proyecto1/src/pruebas/pruebas_mkfs.sh

void Mkfs::format(){
    Algorithms a;
    // Encontrar la informacion de la particion
    vector<infoPart> parts = *(this->getInfoParts());
    infoPart seleccionada;
    bool encontrada = false;
    for(infoPart inf: parts){
        if(a.areEqualCI(inf.part_id, this->getId())){
            seleccionada = inf;
            encontrada = true;
        }
    }

    if(!encontrada){
        Algorithms::printError("No se encontró el ID. ");
        exit(0);
    }

    // Si es un formateo completo se llena de ceros

    if(a.areEqual(this->getFs(), "3FS")){
        Algorithms::fillWithZeros(seleccionada.part_start, seleccionada.part_size, seleccionada.path);
    }
    int systemType;

    // Calcular numero de inodos
    int numInodos;

    // Conseguir el inicio dependiendo del sistema de archivos
    int inicioBmInodos;

    // Validar que las estructuras quepan en la partición
    int sizeTotal;

    bool esExt3 = false;
    if(a.areEqual(this->getFs(), "3FS")){
        float n = (seleccionada.part_size - sizeof(SuperBloque) -100*sizeof(Journal))/(4 + sizeof(INodo) + 3*sizeof(BloqueArchivos));
        numInodos = floor(n);
        
        systemType = 3;
        
        inicioBmInodos = seleccionada.part_start + sizeof(SuperBloque) + 100*sizeof(Journal);
        
        sizeTotal = sizeof(SuperBloque) + sizeof(Journal) + numInodos* sizeof(INodo) + 3*numInodos*sizeof(BloqueArchivos);

        esExt3 = true;
        
    } else if(a.areEqual(this->getFs(), "2FS")){
        float n = (seleccionada.part_size - sizeof(SuperBloque))/(4 + sizeof(INodo) + 3*sizeof(BloqueArchivos));
        numInodos = floor(n);
        
        systemType = 2;
        
        inicioBmInodos = seleccionada.part_start + sizeof(SuperBloque);

        sizeTotal = sizeof(SuperBloque) + numInodos* sizeof(INodo) + 3*numInodos*sizeof(BloqueArchivos);
    } else {
        Algorithms::printError("No existe el formateo seleccionado. ");
        exit(0);
    }

    if(sizeTotal > seleccionada.part_size){
        string s = "La partición debe por lo menos de " + to_string(sizeTotal) + "bytes.";
        Algorithms::printError(s);
        exit(0);
    }

    /*
        Para un sistema de archivos ext3
        --------------------------------------------------------------------------------
        | SUPERBLOQUE | JOURNAL | BITMAP DE INODOS | BITMAP BLOQUES | INODOS | BLOQUES |
        --------------------------------------------------------------------------------

        Para un sistema de archivos ext2
        ----------------------------------------------------------------------
        | SUPERBLOQUE | BITMAP DE INODOS | BITMAP BLOQUES | INODOS | BLOQUES |
        ----------------------------------------------------------------------
    */

    int inicioBmBloques = inicioBmInodos + numInodos;

    int inicioInodos = inicioBmBloques + 3*numInodos;

    int inicioBloques = inicioInodos + numInodos * sizeof(INodo);


    // Crear superbloque

    SuperBloque superBloque;
    superBloque.s_filesystem_type = systemType;
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
    superBloque.s_bm_inode_start=inicioBmInodos;
    superBloque.s_bm_block_start=inicioBmBloques;
    superBloque.s_inode_start= inicioInodos;
    superBloque.s_block_start= inicioBloques;

    

    // Escribir superbloque

    FILE * file;
    file=fopen(seleccionada.path.c_str(),"rb+"); 
    if(file==NULL){
        a.printError("No se pudo escribir el superbloque");
        exit(1);
    }

    fseek(file, seleccionada.part_start, SEEK_SET);
    fwrite(&superBloque, sizeof(superBloque), 1, file);
    
    if(esExt3){
        // Escribir Journals
        Journal journal;
        journal.journal_tipo_operacion[0]='-';
        journal.journal_tipo='-';
        journal.journal_nombre[0]='\0';
        journal.journal_contenido[0]='\0';
        journal.journal_fecha[0]='\0';
        journal.journal_propietario[0] = '\0';
        journal.journal_permisos=-1;

        int inicioJournal = seleccionada.part_start + sizeof(SuperBloque);
        fseek(file, inicioJournal, SEEK_SET);
        fwrite(&journal, sizeof(Journal), 100, file);
    }
    
    // Escribir bitmaps
    char bmInodos[numInodos];
    char bmBloques[3*numInodos];

    // Se llena el bitmap de inodos y bloques
    for(int i=0;i<numInodos;i++){
        bmInodos[i]='\0'; 
        bmBloques[i]='\0';
    }

    // Escribir bitmap de inodos en el archivo
    fseek(file, inicioBmInodos, SEEK_SET);
    fwrite(&bmInodos, sizeof(bmInodos), 1, file);


    // Escribir bitmap de bloques en el archivo
    fseek(file, inicioBmBloques, SEEK_SET);
    fwrite(&bmBloques, sizeof(bmBloques), 1, file);

    

    fclose(file);

    // Crear inodo de carpeta Raiz

    INodo inodo;
    inodo.i_uid = 1;
    inodo.i_gid = 1;
    inodo.i_size = 0;
    stpcpy(inodo.i_atime, a.obtainDate().c_str());
    stpcpy(inodo.i_ctime, a.obtainDate().c_str());
    stpcpy(inodo.i_mtime, a.obtainDate().c_str());
    for (size_t i = 0; i < 15; i++)
    {
        inodo.i_block[i] = -1;
    }
    inodo.i_block[0] = 0;
    inodo.i_type = '0';
    inodo.i_perm = 001001664;
    
    Algorithms::writeInode(inicioInodos, inicioBmInodos, 0, seleccionada.path, inodo);

    // Se crea el bloque de la carpeta '/'
    BloqueCarpeta b;
    Content cont; 
    for (size_t i = 0; i < 4; i++)
    {
        b.b_content[i] = cont;
    }
    // Se apunta hacia el inodo del users.txt
    stpcpy(b.b_content->b_name, "users.txt");
    b.b_content->b_inodo = 1;

    Algorithms::writeBlockCarpeta(inicioBloques, inicioBmBloques, 0, seleccionada.path, b);

    // Crear inodo de carpeta Raiz

    INodo inodo1;
    inodo1.i_uid = 1;
    inodo1.i_gid = 1;
    inodo1.i_size = 22;
    stpcpy(inodo1.i_atime, a.obtainDate().c_str());
    stpcpy(inodo1.i_ctime, a.obtainDate().c_str());
    stpcpy(inodo1.i_mtime, a.obtainDate().c_str());
    for (size_t i = 0; i < 15; i++)
    {
        inodo1.i_block[i] = -1;
    }
    inodo1.i_block[0] = 0;
    inodo1.i_type = '1';
    inodo1.i_perm = 001001664;
    
    Algorithms::writeInode(inicioInodos, inicioBmInodos, 1, seleccionada.path, inodo1);

    BloqueArchivos ba;

    stpcpy(ba.b_content,"1,G,root\n1,U,root,123\n"); 
    
    Algorithms::writeBlockArchivos(inicioBloques, inicioBmBloques, 1, seleccionada.path, ba);
}
