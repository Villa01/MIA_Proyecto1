using namespace std;
#include <stdio.h>
#include <iostream>
#include "./analizador/driver.h"


//extern int yyparse(); 

int p;
int main(int argc, char *argv[])
{

    string p="---Ingese un comando, por favor. \n";
    string line;

    while(line!="salir"){    

        cout <<"\x1B[32m"<< p<<"\e[0m";
        fflush(stdin);
        getline(cin, line);
        if(line!="salir"){
            if(!line.empty()){

               // El driver es el encargado de inicializar el interprete
				Driver driver;
				driver.parseWithText(line);

            }
        }

    }
    
	return 0;
}