#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include "../headers/medicos.h"
#include "../headers/indextuple.h"

using namespace std;
class MedicosFile{
private:
    string dataFileDir;
    string idxCodeDir;
    string idxNameDir;

    fstream dataFileStream;
    fstream idxCodeStream;
    fstream idxNameStream;

    list<IndexTuple<Nombre>> listIdxName;
    list<IndexTuple<string>> listIdxCode;
public:
    MedicosFile(){
        dataFileDir = "backups/medicos-file.txt";
        idxCodeDir = "backups/medicosCode-file.txt";
        idxNameDir = "backups/medicosName-file.txt";
    }
    ~MedicosFile(){
        if(dataFileStream.is_open())
            dataFileStream.close();
        if(idxCodeStream.is_open())
            idxCodeStream.close();
        if(idxNameStream.is_open())
            idxNameStream.close();
    }
    void addData(Medico &m){
        dataFileStream.open("backups/medicos-file.txt", ios::app);
        dataFileStream << m;
        reindex();
    }
    int findDataByName(Nombre &name) const;
    int findDataByCode(string &code) const;
    Medico retrieve(int &idx);
    void reindex(){
        list<IndexTuple<>> myListTupleName;
        list<IndexTuple<>> myListTupleCode;
        IndexTuple<> tupleName;
        IndexTuple<> tupleCode;
        string dirtyLine, cleanLine, aux;
        long long index;
        Medico m;
        dataFileStream.open("backups/medicos-file.txt",ios::in);
        if (!dataFileStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-file");
        // Ciclo para leer todos los médicos del archivo de médicos
        while(!dataFileStream.eof()){
            // Sacar el índice del puntero de lectura para su posición
            index = dataFileStream.tellg();
            getline(dataFileStream, dirtyLine, '#');
            if(dirtyLine.empty())
                continue;
            if(dirtyLine[0] == '0')
                continue;
            cleanLine = dirtyLine.substr(2);
            stringstream iss(cleanLine);
            iss >> m;
            iss.clear();

            // Se llena la tupla de código
            tupleCode.setIndex(index);
            aux = m.getCodigoEmpleado();
            tupleCode.setData(aux);
            myListTupleCode.push_back(tupleCode);

            // Se llena la tupla de nombre
            tupleName.setIndex(index);
            aux = m.getNombre();
            for(auto &i : cleanLine)
                i = (char)toupper(i);
            tupleName.setData(aux);
            myListTupleName.push_back(tupleName);
        }

        // Ordenar la lista por nombre
        myListTupleName.sort();
        myListTupleName.unique();
        // Ordenar la lista por código
        myListTupleCode.sort();
        myListTupleCode.unique();

        // Grabanado a archivo de índice CÓDIGO
        idxCodeStream.open(idxCodeDir,ios::out | ios::trunc);
        if (!idxCodeStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-code'");
        listTofile(myListTupleCode,idxCodeStream);

        // Grabando a archivo de índice NOMBRE
        idxNameStream.open(idxNameDir,ios::out | ios::trunc);
        if (!idxNameStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-name'");
        listTofile(myListTupleName,idxNameStream);
    }
    void delData();
    list<Medico> fileToList(){ // + Cuando agregan
        list <Medico> myList;
        string line;
        Medico m;
        stringstream iss(line);
        dataFileStream.open("backups/medicos-file.txt");
        if (!dataFileStream.is_open())
            throw ios::failure("Archivo no encontrado");
        while(getline(dataFileStream, line, '#')){
            if(line[0] == 0)
                continue;
            line.erase(0,2);
            iss >> m;
            myList.push_back(m);
        }
        return myList;
    }
    template <class T>
    fstream& listTofile(list<T> &myList, fstream &myFStream){  // + Lista y archivo
        for(auto iterator = myList.begin();iterator != myList.end();iterator++)
            myFStream << "1*" << *iterator << '#';
        return myFStream;
    }
    void clear();
    void compress();
};
