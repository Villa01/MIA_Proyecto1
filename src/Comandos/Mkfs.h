
#include <vector>
#include <string>

#include "../Clases/Comando.h"
#include "../Clases/Estructuras.h"
#include "../Clases/Algorithms.h"

class Mkfs: public Comando {

    public:
        Mkfs(vector<infoPart> *infoParts);


        void agregarParametros(vector<Parametro>);
        void assignParameters();
        void format();

    private:
        vector<infoPart> *infoParts;
        string type;
        string id;
        string fs;

        void setInfoParts(vector<infoPart> *infoParts){ this->infoParts = infoParts;}
        void setType(string type){ this->type = type;}
        void setId(string id){this->id = id;}
        void setFs(string fs){this->fs = fs;}

        vector<infoPart>* getInfoParts(){return this->infoParts;}
        string getType(){ return this->type;}
        string getId(){ return this->id;}
        string getFs(){ return this->fs;}

};