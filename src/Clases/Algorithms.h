

#ifndef ALGORITHMS
#define ALGORITHMS
using namespace std;

#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include "Estructuras.h"


class Algorithms {


    public:
        Algorithms();
        bool areEqual(string, string);
        bool areEqualCI(string, string);
        EBR obtain_ebr(int, string);
        int searchPosition(string s, vector<string>v);
        Mbr obtainMbr(string path);
        string obtainDate();
        string toUpper(string s);
        vector<EBR> obtain_ebr_list(Partition, string);
        void writeMbr(Mbr, string);
        void showMbrInfo(string);
        void printPartitions(vector<Partition>, string);
        void printPartition(Partition, string);
        void print_ebr_list(vector<EBR>);
        void print_ebr(EBR);
        static void writeJournal(Journal journal, int inicioJournals, string path);
        static void fillWithZeros(int start, int size, string path);
        static void printError(string err);
        static void printWarning(string war);
        static void printInfo(string info);
        static SuperBloque obtainSuperBloque(int start, string path);
        static void writeInode(int inicioInodos, int inicioBitmap, int numInodo, string path, INodo inodo);
        static void writeBlockArchivos(int inicioBloques, int inicioBitmap, int numBloque, string path, BloqueArchivos bloque);
        static void writeBlockCarpeta(int inicioBloques, int inicioBitmap, int numBloque, string path, BloqueCarpeta bloque);
        static void writeBlockApuntador(int inicioBloques, int inicioBitmap, int numBloque, string path, BloqueApuntadores bloque);

    
};

#endif