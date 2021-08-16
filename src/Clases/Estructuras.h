#ifndef ESTRUCTURAS
#define ESTRUCTURAS


#include <string>

typedef struct {
    char part_status;
    char part_type;
    char part_fit;
    int part_start;
    int part_size;
    char part_name[16];
}Partition;

typedef struct {
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
}EBR;

typedef struct{
    int mbr_tamano;
    char mbr_fecha_creacion[16];
    int mbr_disk_signature;
    char disk_fit;
    Partition mbr_partition1;
    Partition mbr_partition2;
    Partition mbr_partition3;
    Partition mbr_partition4;

}Mbr;




class Estructuras {
    public:
        Estructuras();
};

#endif