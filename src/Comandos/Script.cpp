
#include "Script.h"

using namespace std;

Script::Script(vector<Parametro> params){
    this->setPath(params[0].getValor());
    readText();
}

void Script::readText(){
    std::ifstream t;
    int length;
    t.open(this->getPath());     
    t.seekg(0, std::ios::end);    
    length = t.tellg();           
    t.seekg(0, std::ios::beg);    
    char buffer[length];
    t.read(buffer, length);       
    t.close();   

    executeCommands(buffer);
}

void Script::executeCommands(char text[]){

    Driver driver;
	driver.parseWithText(text);    
}

void Script::executeCommand(char text[]){

}

void Script::setPath( string path ){
    this->path = path;
}

string Script::getPath(){
    return this->path;
}



