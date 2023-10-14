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
        // + TODO fileToList y poblar las dos listas en caso de que se quiera buscar de primeras
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
    int findDataByName(Nombre &name) const{

    }
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
            // Si el booleano que indica si el índice está activo es cero, se ignora
            if(dirtyLine[0] == '0')
                continue;
            // ? Se limpia la línea quitándole el booleano y el separador de campo
            cleanLine = dirtyLine.substr(2);
            // Creación de un string stream con la línea limpia
            stringstream iss(cleanLine);
            // El stream se mete a médico
            iss >> m;
            // Limpieza del stream
            iss.clear();

            // Se llena la tupla de código con el médico obtenido del string stream y se agrega a la lista correspondiente
            tupleCode.setIndex(index);
            aux = m.getCodigoEmpleado();
            tupleCode.setData(aux);
            myListTupleCode.push_back(tupleCode);

            // Se llena la tupla de nombre con el médico obtenido del string stream y se agrega a la lista correspondiente
            tupleName.setIndex(index);
            aux = m.getNombre();
            for(auto &i : cleanLine)
                i = (char)toupper(i);
            tupleName.setData(aux);
            myListTupleName.push_back(tupleName);
        }
        // Ordenar la lista por nombre y quitar duplicados
        myListTupleName.sort();
        myListTupleName.unique();
        // Ordenar la lista por código y quitar duplicados
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

    // + Lista exclusiva para médico
    list<Medico> fileToList(const string &targetFile){
        list<Medico> myList;
        string line;
        Medico m;
        stringstream iss(line);
        ifstream ifs(targetFile);
        if (!ifs.is_open())
            throw ios::failure("Archivo no encontrado");
        while(getline(ifs, line, '#')){
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
