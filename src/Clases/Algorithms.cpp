

#include "Algorithms.h"


Algorithms::Algorithms(){

}

void Algorithms::printError(string err){
    std::cout <<"\e[0;31m"<< "--- ERROR: "<<err << std::endl;
}

void Algorithms::printWarning(string war){
    std::cout <<"\e[0;33m"<< "--- WARNING: "<<war << std::endl;
}

void Algorithms::printInfo(string info){
    cout<<"\e[0;36m--- INFO: "<<info<<endl;
}

int Algorithms::searchPosition(string s, vector<string> v){


    for (int i = v.size() - 1; i >= 0; i--)
    {
        if(this->areEqual(this->toUpper(s), this->toUpper(v[i]))){
            return v.size()-1-i;
        }
    }

    return -1;
}

Mbr Algorithms::obtainMbr(string path){
    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", path.c_str());
        exit(1);
    }

    fseek(file, 0, SEEK_SET);

    Mbr mbr;

    fread(&mbr, sizeof(Mbr), 1, file);
    fclose(file);
    return mbr;
}

void Algorithms::writeMbr(Mbr mbr, string path){
    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        this->printError("No se pudos escribir el mbr");
        exit(1);
    }

    fseek(file, 0, SEEK_SET);

    fwrite(&mbr, sizeof(Mbr), 1, file);
    fclose(file);
}


void Algorithms::showMbrInfo(string path){
    Mbr mbr = this->obtainMbr(path);

    printf("\x1B[32m--- INFO: Resumen MBR\n");
    cout<<"mbr_disk_signature: "<<mbr.mbr_disk_signature<<endl;
    cout<<"mbr_fecha_creacion: "<<mbr.mbr_fecha_creacion<<endl;
    cout<<"disk_fit: "<<mbr.disk_fit<<endl;
    cout<<"mbr_tamano: "<<mbr.mbr_tamano<<endl;

    vector<Partition> partitions{mbr.mbr_partition1, mbr.mbr_partition2, mbr.mbr_partition3, mbr.mbr_partition4};
    this->printPartitions(partitions, path);
}


void Algorithms::printPartitions(vector<Partition> partitions, string path){
    cout<<"\x1B[32m--- INFO: Info particiones"<<endl;
    for(Partition partition : partitions){
        if(partition.part_status == '1'){
            this->printPartition(partition, path);
        }
    }
}

void Algorithms::printPartition(Partition partition, string path){
    string s(1,partition.part_type);
    cout<<"-------------------------------------------------"<<endl;
    cout<<"part_name: "<<partition.part_name<<endl;
    cout<<"part_size: "<<partition.part_size<<endl;
    cout<<"part_start: "<<partition.part_start<<endl;
    cout<<"part_fit: "<<partition.part_fit<<endl;
    cout<<"part_type: "<<partition.part_type<<endl;
    if(this->areEqual(s, "E")){
        vector<EBR> ebr_list = this->obtain_ebr_list(partition, path);
        this->print_ebr_list(ebr_list);
    }

    cout<<endl;
}


vector<EBR> Algorithms::obtain_ebr_list(Partition extended,string path){
    vector<EBR> ebr_list;

    int start_position = extended.part_start;
    while(start_position != -1){

        EBR ebr = this->obtain_ebr(start_position, path);
        if(ebr.part_status == '1'){
            start_position = ebr.part_next;
            ebr_list.push_back(ebr);
        } else {
            break;
        }
    }


    return ebr_list;
}

void Algorithms::print_ebr_list(vector<EBR> ebr_list){
    cout<<endl;
    cout<<"\x1B[32m--- INFO: Info particiones logicas"<<endl;
    for(EBR ebr: ebr_list){
        if(ebr.part_status == '1'){
            this->print_ebr(ebr);
        }
    }
    cout<<endl;
}

void Algorithms::print_ebr(EBR partition){
    cout<<endl;
    cout<<"part_name: "<<partition.part_name<<endl;
    cout<<"part_size: "<<partition.part_size<<endl;
    cout<<"part_start: "<<partition.part_start<<endl;
    cout<<"part_fit: "<<partition.part_fit<<endl;
    cout<<"part_next: "<<partition.part_next<<endl;
    cout<<"part_status: "<<partition.part_status<<endl;
}

EBR Algorithms::obtain_ebr(int start_postion, string path){

    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", path.c_str());
        exit(1);
    }

    fseek(file, start_postion, SEEK_SET);

    EBR ebr;

    fread(&ebr, sizeof(ebr), 1, file);
    fclose(file);
    return ebr;
}

string Algorithms::toUpper(string s){
    string sUpper = s;
    std::transform(sUpper.begin(), sUpper.end(),sUpper.begin(), ::toupper);
    return sUpper;
}

bool Algorithms::areEqual(string s, string d){
    if(strcmp(s.c_str(),d.c_str())==0){
        return true;
    }
    return false;
    
}

bool Algorithms::areEqualCI(string s, string d){
    if(strcmp(this->toUpper(s).c_str(),this->toUpper(d).c_str())==0){
        return true;
    }
    return false;
    
}

string Algorithms::obtainDate(){
    time_t time = std::time(0);
    tm* now = localtime(&time);
    return  to_string(now->tm_mday) + "/" +
                   to_string(now->tm_mon) + "/" +
                   to_string(now->tm_year) + " " +
                   to_string(now->tm_hour) + ":" +
                   to_string(now->tm_min) + ":" + 
                   to_string(now->tm_sec);

}

void Algorithms::fillWithZeros(int start, int size, string path){
    char *buffer;

    buffer = (char*)malloc(size);

    for (int i = 0; i < size-1; i++)
    {
        buffer[i]='\0';
    }

    FILE *file = fopen(path.c_str(), "rb+");

    fseek(file, start,SEEK_SET);
    fwrite(&buffer,1,1,file);
    free(buffer);
    fclose(file);
}

void Algorithms::writeJournal(Journal journal, int inicioJournals, string path){

    // Buscar en los journals hasta que haya un espacio vacío
    int inicio = inicioJournals;

    FILE *file = fopen(path.c_str(), "rb+");
    Journal temp;
    do {
        fseek(file, inicio, SEEK_SET);
        fread(&temp, sizeof(Journal), 1, file);
        inicio += sizeof(Journal);
        
    } while (temp.journal_nombre[0]!='\0' && inicio < (100*sizeof(Journal)));

    if(inicio > (100*sizeof(Journal))){
        Algorithms::printError("No se pudo escribir el journal");
        exit(1);
    }

    fwrite(&journal, sizeof(Journal), 1, file);

    fclose(file);
}

SuperBloque Algorithms:: obtainSuperBloque(int start, string path){
    FILE *file = fopen(path.c_str(), "rb+");

    SuperBloque superb;
    fseek(file, start, SEEK_SET);
    fread(&superb, sizeof(SuperBloque), 1, file);

    fclose(file);

    return superb;
}

void Algorithms::writeInode(int inicioInodos, int inicioBitmap, int numInodo, string path, INodo inodo){
    int start = sizeof(INodo)*numInodo + inicioInodos;
    int bmStart = inicioBitmap + numInodo;

    FILE *file = fopen(path.c_str(), "rb+");


    // Escribe el inodo
    fseek(file, start, SEEK_SET);
    fwrite(&inodo, sizeof(INodo), 1, file);

    char i = '1';
    // Escribe lo sustituye en el bitmap
    fseek(file, bmStart, SEEK_SET);
    fwrite(&i, sizeof(char), 1, file);

    fclose(file);
}

void Algorithms::writeBlockArchivos(int inicioBloques, int inicioBitmap, int numBloque, string path, BloqueArchivos bloque){
    int start = sizeof(BloqueArchivos)*numBloque + inicioBloques;
    int bmStart = inicioBitmap + numBloque;

    FILE *file = fopen(path.c_str(), "rb+");


    fseek(file, start, SEEK_SET);
    fwrite(&bloque, sizeof(BloqueArchivos), 1, file);

    char i = '1';
    // Escribe lo sustituye en el bitmap
    fseek(file, bmStart, SEEK_SET);
    fwrite(&i, sizeof(char), 1, file);

    fclose(file);
}


void Algorithms::writeBlockCarpeta(int inicioBloques, int inicioBitmap, int numBloque, string path, BloqueCarpeta bloque){
    int start = sizeof(BloqueCarpeta)*numBloque + inicioBloques;
    int bmStart = inicioBitmap + numBloque;

    FILE *file = fopen(path.c_str(), "rb+");


    fseek(file, start, SEEK_SET);
    fwrite(&bloque, sizeof(BloqueCarpeta), 1, file);

    char i = '2';
    // Escribe lo sustituye en el bitmap
    fseek(file, bmStart, SEEK_SET);
    fwrite(&i, sizeof(char), 1, file);

    fclose(file);
}


void Algorithms::writeBlockApuntador(int inicioBloques, int inicioBitmap, int numBloque, string path, BloqueApuntadores bloque){
    int start = sizeof(BloqueApuntadores)*numBloque + inicioBloques;
    int bmStart = inicioBitmap + numBloque;

    FILE *file = fopen(path.c_str(), "rb+");


    fseek(file, start, SEEK_SET);
    fwrite(&bloque, sizeof(BloqueApuntadores), 1, file);

    char i = '3';
    // Escribe lo sustituye en el bitmap
    fseek(file, bmStart, SEEK_SET);
    fwrite(&i, sizeof(char), 1, file);

    fclose(file);
}

void Algorithms::showSBInfo(string path, int start){
    SuperBloque sb = Algorithms::obtainSB(path, start);

    Algorithms::printInfo("Resumen SuperBloque: \n");
    cout<<"s_block_size: "<< sb.s_block_size <<endl;
    cout<<"s_block_start: "<< sb.s_block_start <<endl;
    cout<<"s_blocks_count: "<< sb.s_blocks_count <<endl;
    cout<<"s_bm_inode_start: "<< sb.s_bm_inode_start <<endl;
    cout<<"s_filesystem_type: "<< sb.s_filesystem_type <<endl;
    cout<<"s_first_blo: "<< sb.s_first_blo <<endl;
    cout<<"s_first_ino: "<< sb.s_first_ino <<endl;
    cout<<"s_free_blocks_count: "<< sb.s_free_blocks_count <<endl;
    cout<<"s_free_inodes_count: "<< sb.s_free_inodes_count <<endl;
    cout<<"s_inode_size: "<< sb.s_inode_size <<endl;
    cout<<"s_inode_start: "<< sb.s_inode_start <<endl;
    cout<<"s_inodes_count: "<< sb.s_inodes_count <<endl;
    cout<<"s_magic: "<< sb.s_magic <<endl;
    cout<<"s_mnt_count: "<< sb.s_mnt_count <<endl;
    cout<<"s_mtime: "<< sb.s_mtime <<endl;
    cout<<"s_umtime: "<< sb.s_umtime <<endl;
}
    

SuperBloque Algorithms::obtainSB(string path, int start){
    FILE *file = fopen(path.c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", path.c_str());
        exit(1);
    }

    fseek(file, start, SEEK_SET);

    SuperBloque sb;

    fread(&sb, sizeof(SuperBloque), 1, file);
    fclose(file);
    return sb;
}

void Algorithms::printBm(char bm[]){
    string c;
    for (size_t i = 0; i < strlen(bm); i++)
    {
        c.push_back(bm[i]);
    }
    cout<<c<<endl;
}



void Algorithms::printInodo(string path, int inicioInodo, int numInodo){
    INodo inodo = Algorithms::obtainInodo(path, inicioInodo, numInodo);
    Algorithms::printInfo("Resumen Inodo");
    cout<<"i_atime: "<< inodo.i_atime <<endl;
    cout<<"i_block: "<< inodo.i_block <<endl;
    cout<<"i_ctime: "<< inodo.i_ctime <<endl;
    cout<<"i_gid: "<< inodo.i_gid <<endl;
    cout<<"i_mtime: "<< inodo.i_mtime <<endl;
    cout<<"i_perm: "<< inodo.i_perm <<endl;
    cout<<"i_size: "<< inodo.i_size <<endl;
    cout<<"i_type: "<< inodo.i_type <<endl;
    cout<<"i_uid: "<< inodo.i_uid <<endl;
}

INodo Algorithms::obtainInodo(string path, int inicioInodo, int numInodo){
    FILE *file = fopen(path.c_str(), "rb+");
    if(file == NULL){
        Algorithms::printError("No se pudo abrir el archivo para encontrar el inodo.");
        exit(1);
    }

    int start = sizeof(INodo)*numInodo + inicioInodo;

    INodo inodo;
    fseek(file, start, SEEK_SET);
    fread(&inodo, sizeof(INodo), 1, file);
    fclose(file);
    return inodo;
}