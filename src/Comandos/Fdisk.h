
#include "../Clases/Comando.h"
#include "../Clases/Algorithms.h"
#include "../Clases/Estructuras.h"
#include <vector>

class Fdisk : Comando
{
private:
    int add_num;
    int size;
    string delete_type;
    string fit;
    string name;
    string path;
    string type;
    string units;
    int option;
    bool error = false;

    void create_partition();
    void delete_partition();
    void add_storage();
    vector<Partition> sort_partition_vector(vector<Partition>);
    int search_empty_partition(vector<Partition>);
    void read_mbr();

    void set_add_num(int);
    void set_error(bool);
    void set_size(int);
    void set_delete_type(string);
    void set_fit(string);
    void set_name(string);
    void set_option(int);
    void set_path(string);
    void set_type(string);
    void set_units(string);

public:
    Fdisk();
    ~Fdisk();
    void agregarParametros(vector<Parametro>);
    void assignParameters();
    void start_action();


    int get_add_num();
    bool get_error();
    int get_size();
    string get_delete_type();
    string get_fit();
    string get_name();
    int get_option();
    string get_path();
    string get_type();
    string get_units();

    
};

