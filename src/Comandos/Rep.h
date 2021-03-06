
#include <vector>
#include <string>
#include <fstream>
#include "../Clases/Comando.h"
#include "../Clases/Estructuras.h"
#include "../Clases/Algorithms.h"



class Rep: public Comando {

    public:
        Rep(vector<infoPart> *infoParts);


        void agregarParametros(vector<Parametro>);
        void assignParameters();
        void repMbr();
        void selectReport();
        void generateDot(string content, string path);

    private:
        vector<infoPart> *infoParts;
        string name;
        string path;
        string ruta;
        int root;
        string id;
        string pathOrigen;
        string pathDestino;
        string nombreReporte;
        string extension;

        string writeMbrReport();
        string writeDiskReport();
        void executeCommand();
        void obtenerInfoReportes(string strOrigen, string strDestino);

        // Setters & Getters

        void setInfoParts(vector<infoPart> *infoParts){ this->infoParts = infoParts;}
        void setName(string name){this->name = name;}
        void setPath(string path){this->path = path;}
        void setPathOrigen(string path){this->pathOrigen = path;}
        void setPathDestino(string path){this->pathDestino = path;}
        void setNombreReporte(string n){this->nombreReporte = n;}
        void setRuta(string ruta){this->ruta = ruta;}
        void setExtension(string ext){this->extension = ext;}
        void setRoot(int root){this->root = root;}
        void setId(string id){this->id = id;}

        vector<infoPart>* getInfoParts(){return this->infoParts;}
        string getName(){return this->name;}
        string getPath(){return this->path;}
        string getPathOrigen(){return this->pathOrigen;}
        string getPathDestino(){return this->pathDestino;}
        string getNombreReporte(){return this->nombreReporte;}
        string getRuta(){return this->ruta;}
        string getExtension(){return this->extension;}
        int getRoot(){return this->root;}
        string getId(){ return this->id;}


};