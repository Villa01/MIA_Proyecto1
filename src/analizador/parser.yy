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
   class Comando;
   class Parametro;
   class Mkdisk;

}
%{
   using namespace std;
   #include <stdio.h>
   #include <iostream>
   #include <string>
   #include <vector>
   
   #include "driver.h"
%}


/******* TERMINALES ********/
%token <std::string> NUM"NUM" SIZE"SIZE" F"F" PATH"PATH" U"U" BF"BF" FF"FF" WF"WF" K"K" M"M" RUTA"RUTA" MKDISK"MKDISK" RMDISK"RMDISK"
%token GUION"GUION" IGUAL"IGUAL" NEXT_LINE"NEXT_LINE"


/******* NO TERMINALES ********/
%start inicio;
%type <Parametro> parametro
%type <Comando> comando
%type <std::vector<Parametro>> lista_param
%type <std::string> atributo nom_param


%%

   inicio : lista_comandos NEXT_LINE
         { 
            //printf("Primer nivel del arbol\n");
         }
          ;

   lista_comandos : lista_comandos comando  
                  { 
                     //printf("Lista de comandos\n");
                  }
                  | comando                
                  { 
                     //printf("Comando individual\n");
                  }
                  ;

   comando : MKDISK lista_param      
               {
                  //printf("Mkdisk con parametros\n");
                  Mkdisk m;
                  m.agregarParametros($2);
                  m.assignParameters();
               }
            ;
   
   lista_param :  lista_param parametro   
                  {
                     //printf("Lista de parametros\n");
                     $$=$1;
                     $$.push_back($2);
                  }
               | parametro                
                  {  
                     //printf("parametro individual\n");
                     vector<Parametro> params;
                     params.push_back($1);
                     $$ = params;
                  }
               ;
   
   parametro : GUION nom_param IGUAL atributo 
               {  

                  //printf("Quinto nivel del arbol\n");
                  Parametro param;
                  param.setNombre($2);
                  param.setValor($4);
                  $$ = param;
               }
             ;

   nom_param : SIZE     { $$=$1; }
             | F        { $$=$1; }
             | PATH     { $$=$1; }
             | U        { $$=$1; }
             ;

   atributo : NUM    { $$=$1; }
            | BF     { $$=$1; }
            | FF     { $$=$1; }
            | WF     { $$=$1; }
            | K      { $$=$1; }
            | M      { $$=$1; }
            | RUTA   { $$=$1; }
            ;

%%

void yy::Parser::error( const std::string& error){
  std::cout <<"\e[0;31m"<< error << std::endl;
}
