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
    FILE *file = fopen(this->get_path().c_str(),"rb+");

    if(file ==NULL){
        printf("\e[0;31m--- ERROR: No se pudo encontrar la dirección \'%s\'", this->get_path().c_str());
        return;
    }

    fseek(file, 0, SEEK_SET);

    Mbr mbr;

    fread(&mbr, sizeof(mbr), 1, file);
    fclose(file);
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


    partitions = sort_partition_vector(partitions); // Se ordena de menor a mayor
    // Verificar las reglas de particiones

    // Suma de las primarias y las extendidas debe ser <= 4

    int cont_ext = 0;
    int cont_prim = 0;
    for (size_t i = 0; i < partitions.size(); i++)
    {
        string str_type1(1, partitions[i].part_type);
        if(a.areEqual(str_type1, "E")){
            cont_ext++;
        }

        string str_type(1, partitions[i].part_type);
        if(a.areEqual(str_type, "P")){
            cont_prim++;
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

    int start_byte = sizeof(mbr);
    int end_limit = mbr.mbr_tamano;
    
    // Recorrer todas las particiones de manera inversa

    for (int i = partitions.size()- 1; i >= 0; i--)
    {
    // Verificar que el punto de inicio no sea -1
        if(partitions[i].part_start == -1) {
        // Si es -1 verificar que haya espacio suficiente

            int gap = end_limit - start_byte; 

             if( gap >= byte_size){
                // Si hay espacio suficiente romper el ciclo
                break;
             } 

            // Sino seguir con el ciclo

        } else {
        // Sino es -1 verificar si hay espacio suficiente espacio entre el final de la particion y el end_limit
            int gap = end_limit - (start_byte + partitions[i].part_size);

            if ( gap >= byte_size) {
                // Si hay suficiente espacio poner el start_byte al final de esa particion
                start_byte = partitions[i].part_start + partitions[i].part_size + 1;
            } else {
                // Sino continuar con el ciclo y poner el end_limit en el inicio de la particion
                end_limit = partitions[i].part_start;
            }

        }

        if(i == 0 && start_byte == sizeof(mbr)){
            std::cout <<"\e[0;31m"<< "--- ERROR: No hay espacio suficiente para crear la partición." << std::endl;
            return;
        }
    }

    //Crear particion nueva
    Partition nueva;
    nueva.part_status = '1';
    nueva.part_type = *(this->get_type().c_str());
    nueva.part_fit = *(this->get_fit().c_str());
    nueva.part_start = start_byte;
    nueva.part_size = byte_size;
    strcat(nueva.part_name, this->get_name().c_str());

    int pos = search_empty_partition(partitions);
    if (pos != -1){
        partitions[pos] = nueva;
    } else {
        std::cout <<"\e[0;31m"<< "--- ERROR: no se encontró espacio suficiente para asignar la nueva partición." << std::endl;
    }

    mbr.mbr_partition1 = partitions[0];
    mbr.mbr_partition2 = partitions[1];
    mbr.mbr_partition3 = partitions[2];
    mbr.mbr_partition4 = partitions[3];

    FILE *file2 = fopen(this->get_path().c_str(), "rb+");

    if(file2 != NULL){
        fseek(file2,0,SEEK_SET );
        fwrite(&mbr, sizeof(mbr), 1, file2);
        fclose(file2);
        printf("\x1B[32m--- INFO: Se creó la partición correctamente\n");
    } else {
        printf("\e[0;31m--- ERROR: No se pudo crear la partición.");
    }
    this->read_mbr();
}

void Fdisk::read_mbr(){
    FILE*arch;
    arch=fopen(path.c_str(),"rb+");
    if(arch==NULL){
        //return 0;
    }
    Mbr MBR;
    fseek(arch, 0, SEEK_SET);
    fread(&MBR,sizeof(Mbr),1,arch);
    fclose(arch);

    vector<Partition> mbr_partitions{MBR.mbr_partition1, MBR.mbr_partition2, MBR.mbr_partition3, MBR.mbr_partition4};
    cout<<"\x1B[32m--- INFO: Nueva partición"<<endl;
    for(int i=0;i<4;i++){
        if(mbr_partitions[i].part_status=='1')  {
            std::cout << "PARTICION : "<<i << endl;
            std::cout << "\nPARTICION STATUS : "<<mbr_partitions[i].part_status;
            std::cout << "\nPARTICION TYPE : "<<mbr_partitions[i].part_type;
            std::cout << "\nPARTICION FIT : "<<mbr_partitions[i].part_fit;
            std::cout << "\nPARTICION START : "<<mbr_partitions[i].part_start;
            std::cout << "\nPARTICION SIZE : "<<mbr_partitions[i].part_size;
            std::cout << "\nPARTICION NAME : "<<mbr_partitions[i].part_name;
        }
    }
}


int Fdisk::search_empty_partition(vector<Partition> v){
    for (size_t i = 0; i < v.size(); i++)
    {
        if(v[i].part_status == '0'){
            return i;
        }
    }
    return -1;
}

vector<Partition> Fdisk::sort_partition_vector(vector<Partition> v){
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v.size()-1; j++)
        {
            if(v[j].part_start > v[j+1].part_start) {
                Partition temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }   
    }

    return v;
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