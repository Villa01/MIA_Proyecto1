

#include "Rep.h"


Rep::Rep(vector<infoPart> *infoParts):Comando(){
    this->setInfoParts(infoParts);
    Algorithms a;
    a.printInfo("Generando Reportes");
}

void Rep::agregarParametros(vector<Parametro> params){
    this->setParametros(params);
}

void Rep::assignParameters(){
    Algorithms a;

    vector<string> names = this->getParamsStringNames();
    vector<string> values = this->getParamsStringValues();


    int posId = a.searchPosition("ID", names);

    if (posId == -1){
        a.printError("Por favor, agregue el parametro id");
        exit(1);
    } else {
        this->setId(values[posId]);
    }

    int posName = a.searchPosition("NAME", names);

    if (posName == -1){
        a.printError("Por favor, agregue el parametro name");
        exit(1);
    } else {
        this->setName(values[posName]);
    }

    int posPath = a.searchPosition("PATH", names);

    if (posPath == -1){
        a.printError("Por favor, agregue el parametro path");
        exit(1);
    } else {
        this->setPath(values[posPath]);
    }

    int posRuta = a.searchPosition("RUTA", names);

    if (posRuta == -1){
        a.printError("No se incluyó el parametro ruta");
        exit(1);
    } else {
        this->setRuta(values[posRuta]);
    }

    int posRoot = a.searchPosition("ROOT", names);

    if (posRoot == -1){
        a.printWarning("No se incluyó el parametro root, se usará 0 por defecto");
        this->setRoot(0);
    } else {
        int i = stoi(values[posRoot]);
        this->setRoot(i);
    }
}

void Rep:: selectReport(){
    Algorithms a;
    if(a.areEqualCI(this->getName(),"MBR")){
        string s = this->writeMbrReport();
        this->generateDot(s, this->getPathDestino());
        this->executeCommand();
    } else if(a.areEqualCI(this->getName(),"DISK")){
        cout<<"Reporte disk"<<endl;
    }
}

string Rep:: writeMbrReport(){
    Algorithms a;
    // Obtener informacion de la particion
    vector<infoPart> parts = *(this->getInfoParts());
    infoPart seleccionada;
    bool encontrada = false;
    for(infoPart inf: parts){
        if(a.areEqualCI(inf.part_id, this->getId())){
            seleccionada = inf;
            encontrada = true;
        }
    }

    if(!encontrada){
        Algorithms::printError("No se encontró la particion para generar el reporte. ");
        exit(0);
    }

    string str= seleccionada.path;  
    int num = str.find_last_of("/");  
    string nombre = str.substr(num+1, str.length()-1);

    obtenerInfoReportes(seleccionada.path, this->getPath());

    string s = "digraph grafo{\n\trankdir=\"TB\"\n\tnode [shape = record fontname=Arial];\n\ta [label=\"MBR ";
    Mbr mbr = a.obtainMbr(seleccionada.path);
    s += nombre + "\"]\n\ttablaMbr [\n\t\t shape=plaintext\n\t\tlabel=<\n\t\t\t<table>\n\t\t\t\t";
    s += "<tr>\n\t\t\t\t\t<td>Nombre</td>\n\t\t\t\t\t<td>Valor</td>\n\t\t\t\t</tr>";
    s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>mbr_tamaño</td>\n\t\t\t\t\t<td>"+to_string(mbr.mbr_tamano)+"</td>\n\t\t\t\t</tr>";
    string temp(mbr.mbr_fecha_creacion);
    s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>mbr_fecha_creacion</td>\n\t\t\t\t\t<td>"+temp+"</td>\n\t\t\t\t</tr>";
    s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>mbr_disk_signature</td>\n\t\t\t\t\t<td>"+to_string(mbr.mbr_disk_signature)+"</td>\n\t\t\t\t</tr>";
    temp = mbr.disk_fit;
    s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>Disk_fit</td>\n\t\t\t\t\t<td>"+temp+"</td>\n\t\t\t\t</tr>";

    vector<Partition> partitions = {mbr.mbr_partition1, mbr.mbr_partition2, mbr.mbr_partition3, mbr.mbr_partition4};

    for (int i = 0; i < partitions.size(); i++)
    {
        if(partitions[i].part_status == '0'){
            continue;
        }
        string c(1,partitions[i].part_type);
        
        
        s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_status_"+to_string(i)+"</td>\n\t\t\t\t\t<td>"+partitions[i].part_status+"</td>\n\t\t\t\t</tr>";
        s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_fit_"+to_string(i)+"</td>\n\t\t\t\t\t<td>"+partitions[i].part_fit+"</td>\n\t\t\t\t</tr>";
        s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_start_"+to_string(i)+"</td>\n\t\t\t\t\t<td>"+to_string(partitions[i].part_start)+"</td>\n\t\t\t\t</tr>";
        s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_size_"+to_string(i)+"</td>\n\t\t\t\t\t<td>"+to_string(partitions[i].part_size)+"</td>\n\t\t\t\t</tr>";
        s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_name_"+to_string(i)+"</td>\n\t\t\t\t\t<td>"+partitions[i].part_name+"</td>\n\t\t\t\t</tr>";
        if(a.areEqualCI(c, "E")){
            // Es una particion extendida
            vector <EBR> ebr_list = a.obtain_ebr_list(partitions[i], seleccionada.path);
            
            for (int j = 0; j < ebr_list.size(); j++)
            {   
                s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>EBR_"+to_string(j)+"</td>\n\t\t\t\t</tr>";
                s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_status_"+to_string(j)+"</td>\n\t\t\t\t\t<td>"+ebr_list[j].part_status+"</td>\n\t\t\t\t</tr>";
                s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_fit_"+to_string(j)+"</td>\n\t\t\t\t\t<td>"+ebr_list[j].part_fit+"</td>\n\t\t\t\t</tr>";
                s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_start_"+to_string(j)+"</td>\n\t\t\t\t\t<td>"+to_string(ebr_list[j].part_start)+"</td>\n\t\t\t\t</tr>";
                s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_size_"+to_string(j)+"</td>\n\t\t\t\t\t<td>"+to_string(ebr_list[j].part_size)+"</td>\n\t\t\t\t</tr>";
                s += "\n\t\t\t\t<tr>\n\t\t\t\t\t<td>part_name_"+to_string(j)+"</td>\n\t\t\t\t\t<td>"+ebr_list[j].part_name+"</td>\n\t\t\t\t</tr>";
            }
            
        }
    }
    s += "\n\t\t\t</table>\n\t\t>\n\t];\n\ta->tablaMbr[style=invis];\n}";

    return s;
}

void Rep::obtenerInfoReportes(string strOrigen, string strDestino){
    // Obtener el path donde se va a generar el .dot
    int num = strOrigen.find_last_of("/");
    string path = strOrigen.substr(0, num+1);
    // Eliminar espacios en blanco
    int pos = 0;
    while(path.find(' ', pos)!=-1){
        pos = path.find(' ', pos);
        path.replace(pos, 1, "\\ ");
        pos+=2;
    }
    this->setPathOrigen(path);

    // Obtener el path donde se va a generar la imagen. 
    int num2 = strDestino.find_last_of("/");
    string nombre = strDestino.substr(num2+1, strDestino.length()-1);
    string pathDest = strDestino.substr(0,num2+1);
    pos = 0;
    // Eliminar espacios en blanco
    while(pathDest.find(' ', pos)!=-1){
        pos = pathDest.find(' ', pos);
        pathDest.replace(pos, 1, "\\ ");
        pos+=2;
    }
    pos = 0;
    while(nombre.find(' ', pos)!=-1){
        pos = nombre.find(' ', pos);
        nombre.replace(pos, 1, "\\ ");
        pos+=2;
        
    }
    // Eliminar comillas
    if(!pathDest.find("\"")==-1){
        pathDest.replace(pathDest.find("\""), 1, "");
    }

    if(!nombre.find("\"")==-1){
        nombre.replace(nombre.find("\""), 1, "");
    }

    if(nombre.find(".")!= -1){
        string extension = nombre.substr(nombre.find_last_of(".")+1, nombre.length()-1);
        this->setExtension(extension);
    } else {
        Algorithms::printError("Nombre inválido");
        exit(1);
    }
    
    string n = nombre.substr(0,nombre.length()-4);
    this->setPathDestino(pathDest);
    this->setNombreReporte(n);
}

void Rep::generateDot(string content, string path){
    string newPath = path + this->getNombreReporte() + ".dot";
    
    ofstream file;
    file.open(newPath);
    file<<content<<endl;
    file.close();

}

void Rep::executeCommand(){
    string comando = "dot -T" + this->getExtension() + " " + this->getPathDestino()+ this->getNombreReporte() + ".dot -o " + this->getPathDestino() + this->getNombreReporte() + "."+ this->getExtension() + "\n";
    string s = "Reporte generado, si no se generó la imagen, por favor, ejecute este comando " + comando;
    Algorithms::printInfo(s);
    system(comando.c_str());
}
