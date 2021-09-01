
#include "../Clases/Comando.h"
#include "../Clases/Algorithms.h"
#include "../Clases/Estructuras.h"
#include <vector>

class Fdisk : Comando
{
private:
    bool error = false;
    int add_num;
    int option;
    int size;
    string delete_type;
    string fit;
    string name;
    string path;
    string type;
    string units;

    bool check_for_partition(string, string);
    int first_fit_ebr(vector<EBR>, int &start_byte, int end_limit, int to_fit);
    int first_fit(vector<Partition>, int &start_byte, int &end_limit, int to_fit);
    int search_empty_partition(vector<Partition>);
    Partition get_extended(vector<Partition>);
    vector<EBR> obtain_ebr(Partition extended);
    vector<Partition> sort_partition_vector(vector<Partition>);
    void add_storage();
    void create_l_partition(Mbr, vector<Partition>, int);
    void create_p_e_partition(Mbr, vector<Partition>, int);
    void create_partition();
    void delete_partition();
    void delete_part(Mbr*, string);
    void read_ebr();
    void read_mbr();
    void write_ebr_list(vector<EBR>);
    vector<Partition> get_partitions(Mbr mbr);
    void write_ebr(EBR);
    void fill_with_zeros(int start_byte, int bufferSize);

    void set_add_num(int);
    void set_delete_type(string);
    void set_error(bool);
    void set_fit(string);
    void set_name(string);
    void set_option(int);
    void set_path(string);
    void set_size(int);
    void set_type(string);
    void set_units(string);

public:
    Fdisk();
    ~Fdisk();
    void agregarParametros(vector<Parametro>);
    void assignParameters();
    void start_action();


    bool get_error();
    int get_add_num();
    int get_option();
    int get_size();
    string get_delete_type();
    string get_fit();
    string get_name();
    string get_path();
    string get_type();
    string get_units();

    
};

