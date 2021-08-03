%{
  #include <stdio.h>
  #include <string>
  #include "driver.h"
  #include "parser.tab.hh"
%}


%option noyywrap
%option outfile="scanner.cc" 


DIGIT   [0-9]
NUM     {DIGIT}+("."{DIGIT}+)?
PATH    \"?(\/([^\/\n])*)+\"?

%%


"MKDISK"          { return yy::Parser::make_MKDISK(); }


"SIZE"            { return yy::Parser::make_SIZE(); }
"F"               { return yy::Parser::make_F(); }
"PATH"            { return yy::Parser::make_PATH(); }
"U"               { return yy::Parser::make_U(); }


{NUM}             { return yy::Parser::make_NUM(strtol (yytext, NULL, 10));}
"BF"              { return yy::Parser::make_BF(); }
"FF"              { return yy::Parser::make_FF(); }
"WF"              { return yy::Parser::make_WF(); }
"K"               { return yy::Parser::make_K(); }
"M"               { return yy::Parser::make_M(); }
{PATH}            { return yy::Parser::make_RUTA(); }


"-"               { return yy::Parser::make_GUION(); }
"="               { return yy::Parser::make_IGUAL(); }

[[:blank:]]       {}
.                 { printf("Caracter no reconocido: %s\n",yytext);}
<<EOF>>		      {return yy::Parser::make_FIN();}
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