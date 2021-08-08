

using namespace std;

#include <string>
#include <vector>

#include "../Clases/Comando.h"

class Mkdisk : public Comando {
    
    public:
        Mkdisk();
        void agregarParametros(vector<Parametro>);

        float getSize();
        string getPath();
        string getUnits();
        string getFit();

    private:
        float size;
        string path;
        string units;
        string fit;
        bool errorFlag;

        void assignParameters();

    void setSize(float);
    void setPath(string );
    void setUnits(string);
    void setFit(string);
};