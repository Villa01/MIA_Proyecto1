

using namespace std;


#include <string>
#include <vector>
#include <iostream>
#include "../Clases/Comando.h"
#include "../Clases/Algorithms.h"

class Rmdisk : public Comando {
    
    public:
        Rmdisk();
        void agregarParametros(vector<Parametro>);
        void assignParameters();
        void deleteDisk();

        string getPath();

    private:
        string path;


    void setPath(string);
};