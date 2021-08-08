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
%token GUION"GUION" IGUAL"IGUAL" 
%token <std::string> NUM"NUM" SIZE"SIZE" F"F" PATH"PATH" U"U" BF"BF" FF"FF" WF"WF" K"K" M"M" RUTA"RUTA" MKDISK"MKDISK"


/******* NO TERMINALES ********/
%start inicio;
%type <Parametro> parametro
%type <Comando> nom_com comando
%type <std::vector<Parametro>> lista_param
%type <std::string> atributo nom_param

%%

   inicio : lista_comandos "\n" { //printf("Primer nivel del arbol");}
          ;

   lista_comandos : lista_comandos comando  { //printf("Segundo nivel del arbol\n");}
                  | comando                { //printf("Segundo nivel del arbol\n");}
                  ;

   comando : lista_param nom_com    
               {
                  //printf("Tercer nivel del arbol\n");
                  $2.agregarParametros($1);
                  $$ = $2;
               }
           | nom_com                
               {

                  //printf("Tercer nivel del arbol\n");
                  $$ = $1;
               }
           ;

   nom_com : MKDISK     
               {
                  //printf("Cuarto nivel del arbol\n");
                  $$=Mkdisk();
               }
           ;
   
   lista_param : lista_param parametro    
                  {
                     //printf("Cuarto nivel del arbol\n");
                     $$=$1;
                     $$.push_back($2);
                  }
               | parametro                
                  {  
                     //printf("Cuarto nivel del arbol\n");
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
                  printf(param.getNombre().c_str());
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
  std::cout << error << std::endl;
}
