

using namespace std;


#include <string>
#include <vector>
#include <iostream>
#include "../Clases/Algorithms.h"
#include "../Clases/Comando.h"
#include"../Clases/Estructuras.h"

class Mkdisk : public Comando {
    
    public:
        Mkdisk();
        void agregarParametros(vector<Parametro>);
        void assignParameters();

        float getSize();
        string getPath();
        string getUnits();
        string getFit();
        int getSizeInBytes();
        void showInfo();
        void createDisk();

    private:
        float size;
        int sizeInBytes;
        string path;
        string units;
        string fit;
        bool errorFlag;
        void asignarMbr();
        vector<string> getParamsStringNames();
        vector<string> getParamsStringValues();


    void setSize(float);
    void setPath(string );
    void setSizeInBytes(int);
    void setUnits(string);
    void setFit(string);
};