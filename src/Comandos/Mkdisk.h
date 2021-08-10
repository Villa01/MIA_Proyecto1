

using namespace std;


#include <string>
#include <vector>
#include <iostream>
#include "../Clases/Algorithms.h"
#include "../Clases/Comando.h"

class Mkdisk : public Comando {
    
    public:
        Mkdisk();
        void agregarParametros(vector<Parametro>);
        void assignParameters();

        float getSize();
        string getPath();
        string getUnits();
        string getFit();

    private:
        float size;
        string path;
        string units;
        string fit;
        bool errorFlag;
        vector<string> getParamsString();


    void setSize(float);
    void setPath(string );
    void setUnits(string);
    void setFit(string);
};