
#ifndef SCRIPT
#define SCRIPT

#include <fstream>
#include <string.h>
#include "../analizador/driver.h"
#include "../Clases/Comando.h"

class Script : Comando{

    public:
        Script(vector<Parametro> params);

    private:
        string path;
        void readText();

    void setPath(string path);
    string getPath();
    void executeCommands(char text[]);
    void executeCommand(char text[]);
};


#endif