#include "driver.h"
#include "parser.tab.hh"

void Driver::parse(const std::string& archivo){
  file = archivo;

  runScanner();
  yy::Parser parser(*this);
  parser.set_debug_level(false);
  parser.parse();
  closeFile();
}

void Driver::parseWithText(std::string text){
  runScannerWithText(text);
  yy::Parser parser(*this);
  parser.set_debug_level(false);
  parser.parse();
}