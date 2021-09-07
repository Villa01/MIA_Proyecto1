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
    int disk;
    char letter;
    int part_size;
    int part_start;
    char part_id[5];
}infoPart;


typedef struct{
    char journal_tipo_operacion[10] ; 
    char journal_tipo; 
    char journal_nombre[200]; 
    char journal_contenido[200]; 
    char journal_fecha[16]; 
    char journal_propietario[10]; 
    int journal_permisos; 
}Journal;


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

}SuperBloque;

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
}INodo;

typedef struct {
    char b_name[12];
    int b_inodo;
}Content;

typedef struct {
    Content b_content[4];
}BloqueCarpeta;

typedef struct {
    char b_content[64];
}BloqueArchivos;

typedef struct {
    int b_pointers[16];
}BloqueApuntadores;



class Estructuras {
    public:
        Estructuras();
};

#endif