using namespace std;
#include <stdio.h>
#include "./analizador/driver.h"


extern int yyparse(); 

int p;
int main(int argc, char *argv[])
{

    string p="------------------------------Ingrese un comando------------------------------\n";

    string line;

    while(line!="salir"){    //esto me sirve para seguir leyendo siempre los comandos sin salirme
        cout << p;
        fflush(stdin);
        getline(cin, line);
        if(line!="salir"){
            if(!line.empty()){

                //YY_BUFFER_STATE buffer = yy_scan_string(line.c_str());
				Driver driver;
				driver.parseWithText(line);
            }
        }

    }

	return 0;
}