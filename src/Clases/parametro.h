#ifndef PARAMETRO
#define PARAMETRO
using namespace std;

#include <string>

class Parametro {
    public:
        //Parametro(string, string);
        Parametro();
        string getNombre();
        string getValor();
        void setNombre(string);
        void setValor (string);


    private: 
        string valor;
        string nombre;
};

#endif