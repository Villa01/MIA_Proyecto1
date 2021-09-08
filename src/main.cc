using namespace std;
#include <stdio.h>
#include <iostream>
#include "./analizador/driver.h"

//extern int yyparse(); 

int p;
int main(int argc, char *argv[])
{   
    string line;

    for (int i = 1; i < argc; i++)
    {
        line+= argv[i];
    }
    
    if(!line.empty()){
        // El driver es el encargado de inicializar el interprete
        vector<infoPart> parts;
        Driver driver;
        driver.parts = parts;
        driver.parseWithText(line);
    }
	return 0;
}