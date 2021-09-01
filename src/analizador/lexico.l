%{
  #include <stdio.h>
  #include <string>
  #include "driver.h"
  #include "parser.tab.hh"
%}
%option case-insensitive
%option noyywrap
%option outfile="scanner.cc" 
%option nodefault


DIGIT   [0-9]
NUM     -?{DIGIT}+("."{DIGIT}+)?
PATH    (\"(\/([^\/\n])*)+\")|((\/([^\/\n\ ])*)+)
SALTO   [\n\s\r\t]
CADENA  [A-Za-z0-9]+|(\"[A-Za-z0-9]+\")
COMENTARIO #[^#\n\r]*

%%


"MKDISK"          { return yy::Parser::make_MKDISK(yytext); }
"RMDISK"          { return yy::Parser::make_RMDISK(yytext); }
"FDISK"           { return yy::Parser::make_FDISK(yytext); }
"EXEC"            { return yy::Parser::make_EXEC(yytext);}
"MOUNT"           { return yy::Parser::make_TMOUNT(yytext);}
"UNMOUNT"         { return yy::Parser::make_TUNMOUNT(yytext);}
"MKFS"            { return yy::Parser::make_MKFS(yytext);}



"SIZE"            { return yy::Parser::make_SIZE(yytext); }
"PATH"            { return yy::Parser::make_PATH(yytext); }
"TYPE"            { return yy::Parser::make_TYPE(yytext); }
"DELETE"          { return yy::Parser::make_DELETE(yytext); }
"NAME"            { return yy::Parser::make_NAME(yytext); }
"ADD"             { return yy::Parser::make_ADD(yytext); }



"3FS"             { return yy::Parser::make_TRESFS(yytext); }
"2FS"             { return yy::Parser::make_DOSFS(yytext); }
"FAST"            { return yy::Parser::make_FAST(yytext); }
"FULL"            { return yy::Parser::make_FULL(yytext); }
{PATH}            { return yy::Parser::make_RUTA(yytext); }
{NUM}             { return yy::Parser::make_NUM(yytext);}
"ID"              { return yy::Parser::make_ID(yytext); }
"FS"              { return yy::Parser::make_FS(yytext); }


"BF"              { return yy::Parser::make_BF(yytext); }
"FF"              { return yy::Parser::make_FF(yytext); }
"WF"              { return yy::Parser::make_WF(yytext); }

"K"               { return yy::Parser::make_K(yytext); }
"M"               { return yy::Parser::make_M(yytext); }
"B"               { return yy::Parser::make_B(yytext); }
"P"               { return yy::Parser::make_P(yytext); }
"E"               { return yy::Parser::make_E(yytext); }
"L"               { return yy::Parser::make_L(yytext); }


"U"               { return yy::Parser::make_U(yytext); }
"F"               { return yy::Parser::make_F(yytext); }

"-"               { return yy::Parser::make_GUION(); }
"="               { return yy::Parser::make_IGUAL(); }

{CADENA}          { return yy::Parser::make_CADENA(yytext); }
{SALTO}           { }
{COMENTARIO}      { cout<<"\e[0;36m"<<yytext<<endl;}


[[:blank:]]       {}
.                 { printf("\e[0;31m--- ERROR: Caracter no reconocido: %s\n",yytext);}


%%

void Driver::runScanner(){
    yy_flex_debug = false;
    yyin = fopen (file.c_str (), "r");
    if(yyin == NULL){
        printf("No se encontro el archivo de entrada");
        exit(1);
    }
}

void Driver::runScannerWithText(std::string text){
    yy_flex_debug = true;
    YY_BUFFER_STATE buffer = yy_scan_string(text.c_str());
}

void Driver::closeFile(){
    fclose(yyin);
}