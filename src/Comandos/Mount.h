
#ifndef MOUNT
#define MOUNT

#include "../Clases/Comando.h"
#include "../Clases/Algorithms.h"
#include "../Clases/Estructuras.h"
#include <vector>
#include <string>

class Mount: Comando {

    public:
        Mount(vector<infoPart> *parts);

        void assignParameters();
        void agregarParametros(vector<Parametro> parametros);
        void mount();

    private: 
        string path;
        string name;
        vector<infoPart> *parts;    
        
        int obtainDiskNumber();
        char obtainPartLetter();

        void setPath(string path);
        string getPath();

        void setName(string name);
        string getName();

        
};

#endif