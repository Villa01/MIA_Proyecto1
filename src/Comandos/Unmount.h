
#ifndef UNMOUNT
#define UNMOUNT

#include "../Clases/Comando.h"
#include "../Clases/Algorithms.h"
#include "../Clases/Estructuras.h"
#include <vector>
#include <string>

class Unmount: Comando {

    public:
        Unmount(vector<infoPart> *parts);

        void assignParameters();
        void agregarParametros(vector<Parametro> parametros);
        void unmount();

    private: 
        string id;
        vector<infoPart> *parts;

        void setId(string id);
        string getId();
};

#endif