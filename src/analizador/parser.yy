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
   class Rmdisk;
   class Fdisk;
   class Script;
   class Mount;

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
%token <std::string> MKDISK"MKDISK" RMDISK"RMDISK" FDISK"FDISK" TSCRIPT"TSCRIPT" TMOUNT"TMOUNT" UNMOUNT"UNMOUNT"
%token <std::string> SIZE"SIZE" F"F" PATH"PATH" U"U"  TYPE"TYPE" DELETE"DELETE" NAME"NAME" ADD"ADD" ID"ID"
%token <std::string> NUM"NUM" BF"BF" FF"FF" WF"WF" K"K" M"M" B"B" RUTA"RUTA" P"P" E"E" L"L" FAST"FAST" FULL"FULL" CADENA"CADENA"
%token GUION"GUION" IGUAL"IGUAL" 


/******* NO TERMINALES ********/
%start inicio;
%type <Parametro> parametro
%type <Comando> comando
%type <std::vector<Parametro>> lista_param
%type <std::string> atributo nom_param


%%

   inicio : lista_comandos    {}
          ;

   lista_comandos : lista_comandos comando  {}
                  | comando   {}
                  ;

   comando : MKDISK lista_param      
               {
                  Mkdisk m;
                  m.agregarParametros($2);
                  m.assignParameters();
                  m.createDisk();
               }
            | RMDISK lista_param 
               {
                  Rmdisk r;
                  r.agregarParametros($2);
                  r.assignParameters();
                  r.deleteDisk();
               }
            | FDISK lista_param
               {
                  Fdisk f;
                  f.agregarParametros($2);
                  f.assignParameters();
                  f.start_action();
               }
            | TSCRIPT lista_param
               { 
                  Script s($2);

               }
            | TMOUNT lista_param
               {
                  Mount m(&driver.parts);
                  m.agregarParametros($2);
                  m.assignParameters();
                  m.mount();
               }
            | UNMOUNT lista_param
               {

               }
            ;
   
   lista_param :  lista_param parametro   
                  {
                     $$=$1;
                     $$.push_back($2);
                  }
               | parametro                
                  {  
                     vector<Parametro> params;
                     params.push_back($1);
                     $$ = params;
                  }
               ;
   
   parametro : GUION nom_param IGUAL atributo 
               {  
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
             | TYPE     { $$=$1; }
             | DELETE   { $$=$1; }
             | NAME     { $$=$1; }
             | ADD      { $$=$1; }
             ;

   atributo : NUM    { $$=$1; }
            | BF     { $$=$1; }
            | FF     { $$=$1; }
            | WF     { $$=$1; }
            | K      { $$=$1; }
            | M      { $$=$1; }
            | B      { $$=$1; }
            | RUTA   { $$=$1; }
            | P      { $$=$1; }
            | E      { $$=$1; }
            | L      { $$=$1; }
            | FAST   { $$=$1; }
            | FULL   { $$=$1; }
            | CADENA { $$=$1; }
            ;

%%

void yy::Parser::error( const std::string& error){
  std::cout <<"\e[0;31m--- ERROR:"<< error << std::endl;
}
