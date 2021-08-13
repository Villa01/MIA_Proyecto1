#ifndef COMANDO
#define COMANDO

using namespace std;

#include <vector>
#include <string>
#include "parametro.h"

class Comando {

    public: 
        Comando();
        virtual ~Comando();

        string getNombre();
        vector<Parametro> getParams();

        void agregarParametros(vector<Parametro>);
        virtual void assignParameters();
        

    private:
        string nombre;
        vector<Parametro>params;


    protected:
        void setNombre(string);
        void setParametros(vector<Parametro>);

        vector<string> getParamsStringNames();
        vector<string> getParamsStringValues();

};

#endif