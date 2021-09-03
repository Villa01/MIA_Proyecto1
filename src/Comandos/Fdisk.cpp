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
        exit(1);
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
        if(a.areEqual(str_type, "E") || a.areEqual(str_type, "L") || a.areEqual(str_type, "P")){
            this->set_type(a.toUpper(values[posType]));
        }else {
            std::cout <<"\e[0;31m"<< "--- ERROR: el valor de type es inválido." << std::endl;
            exit(1);
        }
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
        exit(1);
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
                exit(1);
            }
        } else {
            this->set_error(true);  
            std::cout <<"\e[0;31m"<< "--- ERROR: no se incluyó el parametro name, no se puede usar Delete" << std::endl;
            exit(1);
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
        exit(1);
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
    
    Algorithms a;

    Mbr mbr = a.obtainMbr(this->get_path());


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

    if(a.areEqual(this->get_type(), "L")){
        create_l_partition(mbr, partitions, byte_size);
    }

    
    if(a.areEqual(this->get_type(), "E") || a.areEqual(this->get_type(), "P")){
        create_p_e_partition(mbr,partitions, byte_size);
    }
}

/*
* Creación de particiones primarias y extendidas
*/

void Fdisk::create_p_e_partition(Mbr mbr, vector<Partition> partitions, int byte_size){

    // Obtener lugar de creacion de particion
    int start_byte = sizeof(mbr); 
    int end_limit = mbr.mbr_tamano;
    // Recorrer todas las particiones de manera inversa
    first_fit(partitions, start_byte, end_limit, byte_size);
    
    //Crear particion nueva
    Partition nueva;
    nueva.part_status = '1';
    nueva.part_type = *(this->get_type().c_str());
    nueva.part_fit = *(this->get_fit().c_str());
    nueva.part_start = start_byte;
    nueva.part_size = byte_size;
    strcpy(nueva.part_name, this->get_name().c_str());

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

/*
* Creación de particiones lógicas
*/
void Fdisk::create_l_partition(Mbr mbr, vector<Partition> partitions, int byte_size){
    Algorithms a;
    // Validar que exista una particion extendida
    int i;
    for (i = 0; i < partitions.size(); i++)
    {   
        string type(1,partitions[i].part_type);
        if(a.areEqual(type, "E")){
            break;
        }
    }
    vector<EBR> ebr_partitions = a.obtain_ebr_list(partitions[i], this->get_path());
    

    int start_byte = partitions[i].part_start;
    int end_limit = partitions[i].part_start + partitions[i].part_size;

    first_fit_ebr(ebr_partitions, start_byte, end_limit, byte_size);



    if( ebr_partitions.size() > 0){
        for (int i = 0; i < ebr_partitions.size(); i++)
        {
            if( i == ebr_partitions.size() - 1){
                ebr_partitions[i].part_next = start_byte;
            }
        }
        
    }   

    write_ebr_list(ebr_partitions);

    int next_part = -1;
    
    // Crear EBR
    EBR ebr;
    ebr.part_fit = this->get_fit()[0];
    strcpy(ebr.part_name, this->get_name().c_str());
    ebr.part_next = -1;
    ebr.part_size = byte_size;
    ebr.part_start = start_byte;
    ebr.part_status = '1';

    write_ebr(ebr);

    this->read_ebr();
}

/*
* first_fit obtiene el valor del punto de inicio siguiendo el primer ajuste. 
*/
int Fdisk::first_fit(vector<Partition> partitions, int &start_byte, int &end_limit, int to_fit){
    int first_start = start_byte;
    
    // Recorre las particiones desde la ultima hasta la primera
    for (int i = partitions.size()- 1; i >= 0; i--)
    {
    // Verificar que el punto de inicio no sea -1
        if(partitions[i].part_start == -1) {
        // Si es -1 verificar que haya espacio suficiente

            int gap = end_limit - start_byte; 
            if( gap >= to_fit){
                // Si hay espacio suficiente romper el ciclo
                break;
            } 

            // Sino seguir con el ciclo

        } else {
        // Sino es -1 verificar si hay espacio suficiente espacio entre el final de la particion y el end_limit
            int gap = end_limit - (partitions[i].part_start + partitions[i].part_size);
            if ( gap >= to_fit) {
                // Si hay suficiente espacio poner el start_byte al final de esa particion
                start_byte = partitions[i].part_start + partitions[i].part_size + 1;
                break;
            } else {
                // Sino continuar con el ciclo y poner el end_limit en el inicio de la particion
                end_limit = partitions[i].part_start;
            }

        }

        if(i == 0 && start_byte == first_start){
            std::cout <<"\e[0;31m"<< "--- ERROR: No hay espacio suficiente para crear la partición." << std::endl;
            exit(1);
        }
    }

    return start_byte;
}

/*
* first_fit obtiene el valor del punto de inicio siguiendo el primer ajuste. 
*/
int Fdisk::first_fit_ebr(vector<EBR> partitions, int &start_byte, int end_limit, int to_fit){

    int first_start = start_byte;

    for (int i = partitions.size()- 1; i >= 0; i--)
    {
    // Verificar que el punto de inicio no sea -1

        if(partitions[i].part_start == -1) {
        // Si es -1 verificar que haya espacio suficiente

            int gap = end_limit - start_byte; 

            if( gap >= to_fit){
                // Si hay espacio suficiente romper el ciclo
                break;
            } 

            // Sino seguir con el ciclo

        } else {
        // Sino es -1 verificar si hay espacio suficiente espacio entre el final de la particion y el end_limit
            int gap = end_limit - (partitions[i].part_start + partitions[i].part_size);

            if ( gap >= to_fit) {
                // Si hay suficiente espacio poner el start_byte al final de esa particion
                start_byte = partitions[i].part_start + partitions[i].part_size + 1;
                break;
            } else {
                // Sino continuar con el ciclo y poner el end_limit en el inicio de la particion
                end_limit = partitions[i].part_start;
            }

        }

        if(i == 0 && start_byte == first_start){
            std::cout <<"\e[0;31m"<< "--- ERROR: No hay espacio suficiente para crear la partición." << std::endl;
            exit(1);
        }
    }

    return start_byte;
}

/*
*   Imprime la información del mbr
*/
void Fdisk::read_mbr(){
    Algorithms a;

    Mbr MBR = a.obtainMbr(this->get_path());

    vector<Partition> mbr_partitions = this->get_partitions(MBR);
    
    a.printPartitions(mbr_partitions, this->get_path());
    
}

/*
*  Escribe muchos ebr
*/
void Fdisk::write_ebr_list(vector<EBR> ebrs){
    for(EBR ebr : ebrs){
        if(ebr.part_status != '0'){
            this->write_ebr(ebr);
        }
    }
}

/*
* Escribe un ebr en el disco
*/

void Fdisk::write_ebr(EBR ebr){
    FILE *file2 = fopen(this->get_path().c_str(), "rb+");

    if(file2 != NULL){
        fseek(file2,ebr.part_start,SEEK_SET );
        fwrite(&ebr, sizeof(ebr), 1, file2);
        fclose(file2);
        printf("\x1B[32m--- INFO: Se creó la partición correctamente\n");
    } else {
        printf("\e[0;31m--- ERROR: No se pudo crear la partición lógica.");
    }
}

/*
*   Imprime la información de todos los ebr
*/
void Fdisk::read_ebr(){
    FILE*arch;
    arch=fopen(path.c_str(),"rb+");
    if(arch==NULL){
        //return 0;
    }
    Mbr MBR;
    fseek(arch, 0, SEEK_SET);
    fread(&MBR,sizeof(Mbr),1,arch);
    fclose(arch);

    vector<Partition> partitions{MBR.mbr_partition1, MBR.mbr_partition2, MBR.mbr_partition3, MBR.mbr_partition4};

    Algorithms a;
    int i;
    for (i = 0; i < partitions.size(); i++)
    {   
        string type(1,partitions[i].part_type);
        if(a.areEqual(type, "E")){
            break;
        }
    }

    vector<EBR> ebr_partitions = a.obtain_ebr_list(partitions[i], this->get_path());

    
    cout<<"\x1B[32m--- INFO: Particiones"<<endl;
    for(EBR ebr : ebr_partitions){
        cout<<"\tNombre: "<<ebr.part_name<<endl;
        cout<<"\tSize: "<<ebr.part_size<<endl;
        cout<<"\tInicia: "<<ebr.part_start<<endl;
        cout<<"\tFit: "<<ebr.part_fit<<endl;
        cout<<"\tSiguiente ebr: "<<ebr.part_next<<endl;
        cout<<"\tStatus: "<<ebr.part_status<<endl;
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

/*
*   Eliminar particiones
*/
void Fdisk::delete_partition(){

    Algorithms a;

    // Pedir confirmación para eliminar 

    std::cout <<"\e[0;33m"<< "--- WARNING: ¿Está segur@ que desea eliminar la partcion " << this->get_name()<< "? 1. Si 0. No\e[0;37m"<< std::endl;

    char confirm[1];
    cin>>confirm;

    int val = (int)confirm[0];
    int succesful;

    if ( val == 49){
    // Verificar que name y path no sean NULL

        if(a.areEqual(this->get_name(), "")){
            std::cout <<"\e[0;31m"<< "--- ERROR: nombre inválido " << std::endl;
            exit(1);
        } 

        if(a.areEqual(this->get_path(), "")){
            std::cout <<"\e[0;31m"<< "--- ERROR: path inválido " << std::endl;
            exit(1);
        } 

        
        // Verificar que la partición exista
        if(this->check_for_partition(this->get_type(), this->get_name())){
            // Eliminar particion
            Mbr mbr = a.obtainMbr(this->get_path());

            this->delete_part(&mbr, this->get_name());
        } else {
            std::cout <<"\e[0;31m"<< "--- ERROR: No se encontró la partición" << std::endl;
        }
    }
    else if (val == 48) {
        printf("\e[0;36m---INFO: No se ha eliminado la particion \n");
    } else {
        std::cout <<"\e[0;31m"<< "--- ERROR: Valor inválido " << std::endl;
    }

    a.showMbrInfo(this->get_path());
}

/*
*   Elimina una particion de un mbr
*/
void Fdisk::delete_part(Mbr *mbr, string name){
    Algorithms a;

    Partition vacia;
    vacia.part_status='0';
    vacia.part_type='-';
    vacia.part_fit='-';
    vacia.part_start=-1;
    vacia.part_size=-1;
    vacia.part_name[0] = '\0';

    EBR vacio;
    vacio.part_status='0';
    vacio.part_fit= '-';
    vacio.part_start=-1;
    vacio.part_size=-1;
    vacio.part_next = -1;
    vacio.part_name[0] = '\0';
    int delete_from;
    int delete_until;
    if(a.areEqual((*mbr).mbr_partition1.part_name, name)){

        (*mbr).mbr_partition1 = vacia;
        delete_from = (*mbr).mbr_partition1.part_start;
        delete_until = (*mbr).mbr_partition1.part_start + (*mbr).mbr_partition1.part_size;

    } else if(a.areEqual((*mbr).mbr_partition2.part_name, name)){

        (*mbr).mbr_partition2 = vacia;
        delete_from = (*mbr).mbr_partition2.part_start;
        delete_until = (*mbr).mbr_partition2.part_start + (*mbr).mbr_partition1.part_size;

    } else if(a.areEqual((*mbr).mbr_partition3.part_name, name)){

        (*mbr).mbr_partition3 = vacia;
        delete_from = (*mbr).mbr_partition3.part_start;
        delete_until = (*mbr).mbr_partition3.part_start + (*mbr).mbr_partition1.part_size;

    } else if(a.areEqual((*mbr).mbr_partition4.part_name, name)){

        (*mbr).mbr_partition4 = vacia;
        delete_from = (*mbr).mbr_partition4.part_start;
        delete_until = (*mbr).mbr_partition4.part_start + (*mbr).mbr_partition1.part_size;

    } else {
        bool extended = false;
        int pos_extended;
        string p1(1,(*mbr).mbr_partition1.part_type);
        string p2(1,(*mbr).mbr_partition1.part_type);
        string p3(1,(*mbr).mbr_partition1.part_type);
        string p4(1,(*mbr).mbr_partition1.part_type);

        if(a.areEqual(p1, "E")){
            extended = true;
            pos_extended = 1;
        } else if(a.areEqual(p2, "E")){
            extended = true;
            pos_extended = 2;
        } else if(a.areEqual(p3, "E")){
            extended = true;
            pos_extended = 3;
        } else if(a.areEqual(p4, "E")){
            extended = true;
            pos_extended = 4;
        }

        Partition *part;
        if(extended){
            switch (pos_extended)
            {
            case 1:
                part = &(*mbr).mbr_partition1;
                break;
            case 2:
                part = &(*mbr).mbr_partition2;
                break;
            
            case 3:
                part = &(*mbr).mbr_partition3;
                break;

            case 4:
                part = &(*mbr).mbr_partition4;
                break;
            
            default:
                break;
            }

            vector<EBR> ebr_list = a.obtain_ebr_list(*part, this->get_path());

            for (int i = 0; i < ebr_list.size(); i++)
            {
                if(a.areEqual(ebr_list[i].part_name, name)){
                    int pos_next = (*part).part_start + (*part).part_size;

                    if(i< ebr_list.size()-1){
                        pos_next = ebr_list[i+1].part_start;
                    }
                    ebr_list[i-1].part_next = pos_next;

                    delete_from = ebr_list[i].part_start;
                    delete_until = ebr_list[i].part_start + ebr_list[i].part_size;

                } else {
                    std::cout <<"\e[0;31m"<< "--- ERROR: No se encontro la particon, no se borró." << std::endl;
                }
            } 
            this->write_ebr_list(ebr_list);
        } else {
            std::cout <<"\e[0;31m"<< "--- ERROR: No se pudo eliminar la particion" << std::endl;
        }

    }

    if(a.areEqual(this->get_delete_type(), "FULL")){
        this->fill_with_zeros(delete_from, delete_until);
    }
    a.writeMbr(*mbr, this->get_path());
}

/*
*   Llena de ceros y elimina la particion
*/

void Fdisk::fill_with_zeros(int start_byte, int bufferSize){

    char *buffer;

    buffer = (char*)malloc(bufferSize);

    for (int i = 0; i < bufferSize-1; i++)
    {
        buffer[i]='\0';
    }

    FILE *file = fopen(this->get_path().c_str(), "rb+");

    fseek(file, start_byte,SEEK_SET);
    fwrite(&buffer,1,1,file);
    free(buffer);
    fclose(file);
}

/*
*   Verifica si una particion existe
*/

bool Fdisk::check_for_partition(string type, string name){
    Algorithms a;
    Mbr mbr = a.obtainMbr(this->get_path());

    vector<Partition> partitions = this->get_partitions(mbr);

    if(a.areEqual(type, "L")){
        Partition extended = this->get_extended(partitions);

        vector<EBR> ebr_list = a.obtain_ebr_list(extended, this->get_path());


        if(ebr_list.size() == 0){
            return false;
        }

        for(EBR ebr : ebr_list){
            if(a.areEqual(ebr.part_name, name)){
                return true;
            }
        }
        return false;
    } else {
        for(Partition partition : partitions){
            if(a.areEqual(partition.part_name, name)){
                return true;
            }
        }
        return true;
    }
    
}

/*
*   Identificar una particion extendida
*/
Partition Fdisk::get_extended(vector<Partition> partitions){
    Algorithms a;
    // Validar que exista una particion extendida
    int i;
    bool found;
    for (i = 0; i < partitions.size(); i++)
    {   
        string type(1,partitions[i].part_type);
        if(a.areEqual(type, "E")){
            found = true;
            break;
        }
    }

    if(found){
        return partitions[i];
    } else {
        printf("\e[0;36m---INFO: No hay una particion extendida \n");
        exit(1);
    }
}

vector<Partition> Fdisk::get_partitions(Mbr mbr){
    vector<Partition> partitions{mbr.mbr_partition1, mbr.mbr_partition2, mbr.mbr_partition3, mbr.mbr_partition4};
    return partitions;
}

void Fdisk::add_storage(){
    Algorithms a;
    // Obtener el mbr
    Mbr mbr = a.obtainMbr(this->get_path());
    // Verificar si la particion existe
    // Buscar en el mbr
    int partition_index = -1;
    bool found = false;
    if(mbr.mbr_partition1.part_status == '1' && a.areEqual(mbr.mbr_partition1.part_name, this->get_name())){

        partition_index = 1;
        found = true;

    } else if(mbr.mbr_partition2.part_status == '1' && a.areEqual(mbr.mbr_partition2.part_name, this->get_name())){

        partition_index = 2;
        found = true;

    } else if(mbr.mbr_partition3.part_status == '1' && a.areEqual(mbr.mbr_partition3.part_name, this->get_name())){

        partition_index = 3;
        found = true;

    } else if(mbr.mbr_partition4.part_status == '1' && a.areEqual(mbr.mbr_partition4.part_name, this->get_name())){
        partition_index = 4;
        found = true;

    } 

    // Verificar si hay particion extendida
    int extended_index;
    bool extended = false;
    if(mbr.mbr_partition1.part_status == '1'){

        extended_index = 1;
        string s(1, mbr.mbr_partition1.part_type);
        if(a.areEqual(s, "E")){
            extended = true;
        }

    } else if(mbr.mbr_partition2.part_status == '1'){

        extended_index = 2;
        string s(1, mbr.mbr_partition2.part_type);
        if(a.areEqual(s, "E")){
            extended = true;
        }

    } else if(mbr.mbr_partition3.part_status == '1'){

        extended_index = 3;
        string s(1, mbr.mbr_partition3.part_type);
        if(a.areEqual(s, "E")){
            extended = true;
        }

    } else if(mbr.mbr_partition4.part_status == '1'){
        extended_index = 4;

        string s(1, mbr.mbr_partition4.part_type);
        if(a.areEqual(s, "E")){
            extended = true;
        }
    } 

    // Buscar en las ebr si es necesario
    bool isEbr = false;
    int ebr_index;
    vector<EBR> ebr_list;
    Partition *extended_partition;
    cout<<"index "<<extended_index<<endl;
    cout<<"nombre "<<*extended_partition->part_name<<endl;
    if(extended){
        // Obtener la particion extendida
        switch (extended_index)
        {
        case 0:
            extended_partition = &mbr.mbr_partition1;
            cout<<mbr.mbr_partition1.part_name;
            break;
        
        case 1:
            extended_partition = &mbr.mbr_partition2;
            break;

        case 2:
            extended_partition = &mbr.mbr_partition3;
            break;

            
        case 3:
            extended_partition = &mbr.mbr_partition4;
            break;
            
        }
        cout<<"nombre "<<*extended_partition->part_name<<endl;
        ebr_list = a.obtain_ebr_list(*extended_partition, this->get_path());
        int i =0;

        for( EBR ebr : ebr_list){
            cout<<ebr.part_name<<endl;
        }
        for(EBR ebr : ebr_list ){
            if(ebr.part_status == '1' && a.areEqual(ebr.part_name, this->get_name())){
                isEbr = true;
                found = true;
                ebr_index = i;
            }
            i++;
        }
    }

    if(!found){
        printf("\e[0;36m---INFO: No se encontró una partición que coincida \n");
        exit(1);
    }
    // Cambiar parametro size
    int byte_size = this->get_add_num();
    if (a.areEqual(this->get_units(), "K")){
        byte_size *= 1024;
    } else if(a.areEqual(this->get_units(), "M")){
        byte_size *= 1024*1024;
    } else { // Este error no deberia pasar nunca por el analisis léxico
        std::cout <<"\e[0;31m"<< "--- ERROR: Por favor, el parametro U es incorrecto" << std::endl;
        return;
    }

    bool enough_storage = false;
    if(this->get_add_num() >= 0){
        // Si se desea agregar, verificar que haya espacio despues
        if(!isEbr){
        // Verificar extendidas y primarias
            vector<Partition> partitions = this->get_partitions(mbr);
            this->sort_partition_vector(partitions);
            for (int i = 0; i < partitions.size(); i++)
            {
                if(partitions[i].part_status == '1' && a.areEqual(partitions[i].part_name, this->get_name())){
                    int available_storage;
                    if( i == partitions.size()-1){

                        available_storage = mbr.mbr_tamano - partitions[i].part_start - partitions[i].part_size;
                    } else {

                        if(partitions[i+1].part_start == -1){
                            available_storage = mbr.mbr_tamano - partitions[i].part_start - partitions[i].part_size;
                        } else {
                            available_storage = partitions[i+1].part_start - partitions[i].part_start - partitions[i].part_size;
                        }
                    }
                    if(available_storage >= byte_size){
                        enough_storage = true;
                    } else {
                        enough_storage = false;
                    }
                }
            }
        } else {
            for (int i = 0; i < ebr_list.size(); i++)
            {
                if(ebr_list[i].part_status == '1' && a.areEqual(ebr_list[i].part_name, this->get_name())){
                    int available_storage;
                    if( i == ebr_list.size()-1){
                        available_storage =  (extended_partition->part_start +  extended_partition->part_size)- ebr_list[i].part_start - ebr_list[i].part_size;
                    } else {
                        available_storage = ebr_list[i+1].part_start - ebr_list[i].part_start - ebr_list[i].part_size;
                    }
                    if(available_storage >= byte_size){
                        enough_storage = true;
                    } else {
                        enough_storage = false;
                    }
                }
            }
            
        }
    } else {
    // Si se desea eliminar, verificar que la particion tenga espacio suficiente
        if(!isEbr){
        // Verificar extendidas y primarias
            vector<Partition> partitions = this->get_partitions(mbr);
            this->sort_partition_vector(partitions);
            for (int i = 0; i < partitions.size(); i++)
            {
                if(partitions[i].part_status == '1' && a.areEqual(partitions[i].part_name, this->get_name())){
                    int available_storage;
                    available_storage = partitions[i].part_size;               

                    if(available_storage >= abs(byte_size)){
                        enough_storage = true;
                    } else {
                        enough_storage = false;
                    }
                }
            }
        } else {
            for (int i = 0; i < ebr_list.size(); i++)
            {
                if(ebr_list[i].part_status == '1' && a.areEqual(ebr_list[i].part_name, this->get_name())){
                    int available_storage;

                    available_storage = ebr_list[i].part_size;            

                    if(available_storage >= abs(byte_size)){
                        enough_storage = true;
                    } else {
                        enough_storage = false;
                    }
                }
            }
            
        }

    }

    cout<<enough_storage<<endl;

    if(enough_storage){

        if(!isEbr){
        // Cambiar en primarias y extendidas
            vector<Partition> partitions = this->get_partitions(mbr);
            this->sort_partition_vector(partitions);
            for (int i = 0; i < partitions.size(); i++)
            {
                if(partitions[i].part_status == '1' && a.areEqual(partitions[i].part_name, this->get_name())){
                    partitions[i].part_size += byte_size;
                }
            }

            mbr.mbr_partition1 = partitions[0];
            mbr.mbr_partition2 = partitions[1];
            mbr.mbr_partition3 = partitions[2];
            mbr.mbr_partition4 = partitions[3];
            
            a.writeMbr(mbr, this->get_path());

        } else {
            for (int i = 0; i < ebr_list.size(); i++)
            {
                if(ebr_list[i].part_status == '1' && a.areEqual(ebr_list[i].part_name, this->get_name())){
                    ebr_list[i].part_size += byte_size;
                }

            }

            this->write_ebr_list(ebr_list);
            
        }
        printf("\x1B[32m--- INFO: Se cambio el tamaño de la particion\n");

    } else {
        std::cout <<"\e[0;31m"<< "--- ERROR: No hay espacio suficiente" << std::endl;
        exit(1);
    }
    a.showMbrInfo(this->get_path());
    
}

/* Setters & Getters */

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