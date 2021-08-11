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
        //getline(cin, line);
        if(line!="salir"){
            line = "MKDISK -u=k -PATH=/home/erick/Desktop/disk.dk -F=BF  -size=3000\n";
            
            if(!line.empty()){

               // El driver es el encargado de inicializar el interprete
				Driver driver;
				driver.parseWithText(line);


            }
            line = "salir";
        }

    }
    
	return 0;
}