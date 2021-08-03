%skeleton "lalr1.cc" /* -*- C++ -*- */

%defines
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant

%define parse.trace
%define parse.error verbose
%param { Driver& driver }


%code requires
{
   class Driver;
}

%{
   
   #include <string>
   #include <stdio.h>
   #include "driver.h"
   #include <iostream>
%}


/******* TERMINALES ********/
%token MKDISK"MKDISK" SIZE"SIZE" F"F" PATH"PATH" U"U" BF"BF" FF"FF" WF"WF" K"K" M"M" RUTA"RUTA" GUION"GUION" IGUAL"IGUAL" 
%token <float> NUM"NUM"
%token FIN 0 "eof"

/******* NO TERMINALES ********/
%start inicio;

%%

   inicio : lista_comandos {}
          ;

   lista_comandos : lista_comandos comando  {}
                  | comando                {}
                  ;

   comando : lista_param nom_com    {}
           | nom_com                {}
           ;

   nom_com : MKDISK     { printf("Se reconocio MKDISK\n");}
           ;
   
   lista_param : lista_param parametro    {}
               | parametro                {}
               ;
   
   parametro : GUION nom_param IGUAL atributo {}
             ;

   nom_param : SIZE     { printf("Se reconocio SIZE\n"); }
             | F        { printf("Se reconocio F\n"); }
             | PATH     { printf("Se reconocio PATH\n"); }
             | U        { printf("Se reconocio U\n"); }
             ;

   atributo : NUM    { printf("Se reconocio NUM\n"); }
            | BF     { printf("Se reconocio BF\n");}
            | FF     { printf("Se reconocio FF\n");}
            | WF     { printf("Se reconocio WF \n");}
            | K      { printf("Se reconocio K\n");}
            | M      { printf("Se reconocio M\n");}
            | RUTA   { printf("Se reconocio RUTA\n");}
            ;

%%

void yy::Parser::error( const std::string& error){
  std::cout << error << std::endl;
}
