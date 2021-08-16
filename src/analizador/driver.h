#include <string>


#include "../Comandos/Mkdisk.h"
#include "../Comandos/Rmdisk.h"
#include "../Comandos/Fdisk.h"
#include "parser.tab.hh"

#define YY_DECL \
    yy::Parser::symbol_type yylex (Driver& driver)
YY_DECL;

class Driver {
  public:
    void runScanner();
    void runScannerWithText(const std::string text);
    void closeFile();
    void parse(const std::string& archivo);
    void parseWithText(const std::string text);
    std::string file;
};