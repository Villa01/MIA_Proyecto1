#ifndef DRIVER
#define DRIVER

#include <string>


#include "../Comandos/Rep.h"
#include "../Comandos/Mkdisk.h"
#include "../Comandos/Rmdisk.h"
#include "../Comandos/Fdisk.h"
#include "../Comandos/Script.h"
#include "../Comandos/Mount.h"
#include "../Comandos/Unmount.h"
#include "../Comandos/Mkfs.h"
#include "../Clases/Estructuras.h"
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
    vector<infoPart> parts;
    int diskNumber;
};

#endif