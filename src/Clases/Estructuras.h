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


typedef struct{
    char part_name[16];
    std::string path;
    int part_size;
    int part_start;
    char part_id[5];
}infoPart;



typedef struct {
   int s_filesystem_type;
   int s_inodes_count;
   int s_blocks_count;
   int s_free_blocks_count;
   int s_free_inodes_count;
   char s_mtime [16];
   char s_umtime [16];
   int s_mnt_count;
   int s_magic;
   int s_inode_size;
   int s_block_size;
   int s_first_ino;
   int s_first_blo;
   int s_bm_inode_start;
   int s_bm_block_start;
   int s_inode_start;
   int s_block_start;

}superBloque;

typedef struct {
    int i_uid;
    int i_gid;
    int i_size;
    char i_atime [16];
    char i_ctime[16];
    char i_mtime [16];
    int i_block[15];
    char i_type;
    int i_perm;


}iNodo;

typedef struct {
    char b_name[12];
    int b_inodo;
}content;

typedef struct {
    content b_content[64];
}bloqueCarpeta;

typedef struct {
    content b_content[64];
}bloqueArchivos;

typedef struct {
    int b_pointers[16];
}bloqueApuntadores;



class Estructuras {
    public:
        Estructuras();
};

#endif