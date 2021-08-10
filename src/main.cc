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
            line = "MKDISK -PATH=/home/erick/disk.dk -u=k -size=1000";
            
            if(!line.empty()){

               // El driver es el encargado de inicializar el interprete
				Driver driver;
				driver.parseWithText(line);

                // Algorithms a;
                // vector<string> v;
                // v.push_back("PATH");
                // v.push_back("U");
                // v.push_back("SIZE");
                // v.push_back("HOL");
                // int i = a.searchPosition("SIZE", v);
                // printf("%d\n", i);

            }
            line = "salir";
        }

    }
    
	return 0;
}