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
            //line = "MKDISK -PATH=/home/erick/Clases/Archivos/Laboratorio/Disk.dk -U=K -SIZE=1000 \n MKDISK -PATH=/home/erick/Clases/Archivos/Laboratorio/DISCO1.DK -U=K -SIZE=40001 \n MKDISK -PATH=/home/erick/Clases/Archivos/Laboratorio/DISCO2.DK -U=K -SIZE=40002 \n MKDISK -PATH=/home/erick/Clases/Archivos/Laboratorio/DISCO3.DK -U=K -SIZE=40003 \n MKDISK -PATH=/home/erick/Clases/Archivos/Laboratorio/DISCO4.DK -U=K -SIZE=40004";
            
            if(!line.empty()){

               // El driver es el encargado de inicializar el interprete
                vector<infoPart> parts;
				Driver driver;
                driver.parts = parts;
				driver.parseWithText(line);


            }
            line = "salir";
        }

    }
    
	return 0;
}