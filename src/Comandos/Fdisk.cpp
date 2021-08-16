#include "Fdisk.h"



Fdisk::Fdisk()
{
}

Fdisk::~Fdisk()
{
}

void Fdisk::agregarParametros(vector<Parametro> params){
    this->setParametros(params);
}

void Fdisk::assignParameters(){
    
    if(this->getParams().size()==0){
        this->set_error(true);
        std::cout <<"\e[0;31m"<< "--- ERROR: No hay suficientes parametros en el comando MKDISK" << std::endl;
    }

    Algorithms a;
    vector<string> sparams = this->getParamsStringNames();
    vector<string> values = this->getParamsStringValues();
    

    this->set_option(0);

    // Asignar path es obligatorio
    int posP = a.searchPosition("PATH", sparams);

    if (posP == -1){
        this->set_error(true);
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, agregue el parametro path" << std::endl;
        return;
    } else {
        this->set_path(values[posP]);
    }

    // Asignar U
    int posU = a.searchPosition("U", sparams);
    if(posU==-1){
        std::cout <<"\e[0;33m"<< "--- WARNING: no se incluyó el parametro U, se usarán Kb por defecto" << std::endl;
        this->set_units("K");
    } else {
        this->set_units(a.toUpper(values[posU]));
    }

    // Asignar type
    int posType = a.searchPosition("TYPE", sparams);
    if(posType==-1){
        std::cout <<"\e[0;33m"<< "--- WARNING: no se incluyó el parametro Type, se usarán P por defecto" << std::endl;
        this->set_type("P");
    } else {
        string str_type = a.toUpper(values[posType]);
        if(a.areEqual(str_type, "E") || a.areEqual(str_type, "L") || a.areEqual(str_type, "P"))
            this->set_type(a.toUpper(values[posType]));
        else 
            std::cout <<"\e[0;31m"<< "--- ERROR: el valor de type es inválido." << std::endl;
            return;
    }

    // Asignar F
    int posF = a.searchPosition("F", sparams);
    if(posF==-1){
        std::cout <<"\e[0;33m"<< "--- WARNING: no se incluyó el parametro F, se usarán WF por defecto" << std::endl;
        this->set_fit("WF");
    } else {
        this->set_fit(a.toUpper(values[posF]));
    }


    // Asignar NAME
    int posName = a.searchPosition("NAME", sparams);
    if(posName==-1){
        this->set_error(true);
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, agregue el parametro name" << std::endl;
        return;
    } else {
        this->set_name(values[posName]);
    }


    // Asignar DELETE
    int posDelete = a.searchPosition("DELETE", sparams);
    if(posDelete==-1){
        // Si no viene DELETE
    } else {
        if(posName != -1){

            if(posP != -1){
                this->set_delete_type(values[posDelete]);
                this->set_option(1);
            } else {
                this->set_error(true);
                std::cout <<"\e[0;31m"<< "--- ERROR: no se incluyó el parametro path, no se puede usar Delete" << std::endl;
                return;
            }
        } else {
            this->set_error(true);  
            std::cout <<"\e[0;31m"<< "--- ERROR: no se incluyó el parametro name, no se puede usar Delete" << std::endl;
            return;
        }
    }

    // Asignar ADD
    int posAdd = a.searchPosition("ADD", sparams);
    if(posAdd==-1){
        // Si no viene ADD
    } else {
        this->set_option(2);
        this->set_add_num(stoi(values[posAdd]));
    }
    
    // Asignar size
    int posSize = a.searchPosition("SIZE", sparams);
    if(posSize==-1 && posAdd != -1 && posDelete != -1){
        this->set_error(true);
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, agregue el parametro size" << std::endl;
        return;
    } else if(posSize!=-1){
        if(stof(values[posSize])>0) {
            this->set_size(stof(values[posSize]));
        } else {
            this->set_error(true);
            std::cout <<"\e[0;31m"<< "--- ERROR: El parametro size debe ser mayor que 0" << std::endl;
        }
    }
}

void Fdisk::start_action(){

    if(this->get_error()){
        return;
    }

    switch (this->get_option())
    {
    case 0:
        // Crear una particion
        create_partition();
        break;

    case 1:
        // Eliminar una particion
        delete_partition();
        break;

    case 2: 
        // Agregar espacio a una particion
        add_storage();
        break;
    
    default:
        break;
    }
}

void Fdisk::create_partition(){
    // Obtener mbr
    FILE *file = fopen(this->get_path().c_str(),"r+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", this->get_path().c_str());
        return;
    }

    fseek(file, 0, SEEK_SET);

    Mbr mbr;

    fread(&mbr, sizeof(mbr), 1, file);

    Algorithms a;
    int byte_size = this->get_size();

    // Obtener tamanio en bytes

    if (a.areEqual(this->get_units(), "K")){
        byte_size *= 1024;
    } else if(a.areEqual(this->get_units(), "M")){
        byte_size *= 1024*1024;
    } else { // Este error no deberia pasar nunca por el analisis léxico
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, el parametro U es incorrecto" << std::endl;
        return;
    }

    // Obtener las particiones del disco

    vector<Partition> partitions{mbr.mbr_partition1, mbr.mbr_partition2, mbr.mbr_partition3, mbr.mbr_partition4};


    // Verificar las reglas de particiones

    // Suma de las primarias y las extendidas debe ser <= 4

    int cont_ext;
    int cont_prim;
    for (size_t i = 0; i < partitions.size(); i++)
    {
        string str_type(1, partitions[i].part_type);
        if(a.areEqual(str_type, "E")){
            cont_ext++;
        }

        string str_type(1, partitions[i].part_type);
        if(a.areEqual(str_type, "P")){
            cont_ext++;
        }

    }

    if(a.areEqual(this->get_type(), "E")){
        cont_ext++;
    }

    if(a.areEqual(this->get_type(), "P")){
        cont_prim++;
    }

    if(cont_prim+cont_ext > 4){
        std::cout <<"\e[0;31m"<< "--- ERROR: se alcanzó el límite de particiones extendidas y primarias" << std::endl;
        return;
    } else if(cont_ext >1){
        std::cout <<"\e[0;31m"<< "--- ERROR: solo puede haber una partición extendida por disco." << std::endl;
        return;
    } else if( cont_ext < 1 && a.areEqual(this->get_type(), "L")){
        std::cout <<"\e[0;31m"<< "--- ERROR: no se puede crear una partición lógica sin una extendida." << std::endl;
        return;
    }
    

    // Obtener lugar de creacion de particion

    int start_byte = sizeof(mbr) + 1;

    for (int i = 0; i < partitions.size(); i++)
    {
        if(partitions[i].part_status != -1){

            // Verificar si el espacio es suficiente para la particion

            int temp_start = partitions[i].part_start + partitions[i].part_size + 1;
            int temp_end = temp_start + byte_size;
            
            // Busca un espacio entre todas las particiones
            int part_start_b = partitions[i].part_start;
            int part_end = part_start_b + partitions[i].part_size;
            int part_start2;
            if(i+1 < partitions.size()){
                    part_start2= partitions[i+1].part_start;
            } else {
                part_start2 = mbr.mbr_tamano;
            }

            if ( part_end < temp_start && temp_end < part_start2){
                // Asignar particion al disco
            }
            
            
        }
    }
    

    // Crear particion nueva

    //Partition nueva;
    //nueva.part_status = 1;
    //nueva.part_type = *(this->get_type().c_str());
    //nueva.part_fit = *(this->get_fit().c_str());
    //nueva.part_start = 

}

void Fdisk::delete_partition(){

}

void Fdisk::add_storage(){

}


void Fdisk::set_add_num(int num){
    this->add_num = num;
}

void Fdisk::set_error(bool e){
    this->error = e;
}

void Fdisk::set_size(int s){
    this->size = s;
}

void Fdisk::set_delete_type(string d){
    this->delete_type = d;
}

void Fdisk::set_fit(string f){
    this->fit = f;
}

void Fdisk::set_name(string n){
    this->name = n;
}

void Fdisk::set_option(int op){
    this->option = op;
}

void Fdisk::set_path(string p){
    this->path = p;
}

void Fdisk::set_type(string t){
    this->type = t;
}

void Fdisk::set_units(string u ){
    this->units = u;
}

int Fdisk::get_add_num(){
     return this->add_num;
}

bool Fdisk::get_error(){
     return this->error;
}

int Fdisk::get_size(){
     return this->size;
}

string Fdisk::get_delete_type(){
     return this->delete_type;
}

string Fdisk::get_fit(){
     return this->fit;
}

string Fdisk::get_name(){
     return this->name;
}

int Fdisk::get_option(){
     return this->option;
}

string Fdisk::get_path(){
     return this->path;
}

string Fdisk::get_type(){
     return this->type;
}

string Fdisk::get_units(){
     return this->units;
}