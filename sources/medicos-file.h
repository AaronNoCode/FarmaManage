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
        reindex();
        for(auto const &iterator :listIdxCode){
            cout<<iterator.getIndex()<<'\n';
        }
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
    // + Nota, siempre debe estar poblada la lista para poder buscar
    int findDataByName(Nombre &name) const{
        for(const auto & iterator : listIdxName){
            if(iterator.getData() == name)
                return iterator.getIndex();
        }
        // Si el ciclo se termina y no encontró el objeto, retorna -1
            return -1;
    }
    // + Nota, siempre debe estar poblada la lista para poder buscar
    int findDataByCode(string &code) {
        for(const auto &iterator :listIdxCode){
            if(iterator.getData() == code)
                return iterator.getIndex();
        }
        // Si el ciclo se termina y no encontró el objeto, retorna -1
            return -1;
    }
    Medico retrieve(int &idx){
        for(auto const &iterator :listIdxCode){
            if(iterator.getIndex() == idx){
                dataFileStream.open(dataFileDir,ios::in);
                if(!dataFileStream.is_open())
                    throw ios::failure("Archivo no encontrado 'medicos-file'");
                dataFileStream.seekg(idx);
                string aux;
                Medico med;
                getline(dataFileStream, aux, '*');
                if(aux == "0")
                    throw ios::failure("Indice eliminado");
                getline(dataFileStream,aux,'#');
                stringstream iss(aux);
                iss>>med;
                return med;
            }
        }
        throw ios::failure("Indice no existe");
    }
    // + Siempre lee el archivo de médicos y actualiza las listas
    void reindex(){
        list<IndexTuple<>> myListTupleName;
        list<IndexTuple<>> myListTupleCode;
        IndexTuple<> tupleName;
        IndexTuple<> tupleCode;
        string dirtyLine, cleanLine, aux;
        long long index;
        Medico m;
        dataFileStream.open(dataFileDir,ios::in);
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
            listIdxCode.push_back(tupleCode);

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

        fileToList(idxNameDir,listIdxName);
        fileToList(idxCodeDir,listIdxCode);
    }
    void delData(int &idx){
        for(auto const &iterator : listIdxCode){
            if(iterator.getIndex() == idx){
                dataFileStream.seekp(iterator.getIndex());
                dataFileStream.put('0');
                reindex();
                return;
                // TODO checar si sirve así
            }
        }
        throw ios::failure("Indice inexistente");
    }
    void delData(const Nombre& nombre){
        for(auto const &iterator :listIdxName){
            if(iterator.getData() == nombre){
                dataFileStream.seekp(iterator.getIndex());
                dataFileStream.put('0');
                reindex();
                return;
                // TODO checar si sirve así
            }
        }
    }
    void delData(string &codigo){
        for (auto const &iterator : listIdxCode){
            if (iterator.getData() == codigo){
                dataFileStream.seekp(iterator.getIndex());
                dataFileStream.put('0');
                reindex();
                return;
                // TODO checar si sirve así
            }
        }
    }
    // + Lista exclusiva para médico
    template <class T>
    list<T> fileToList(const string &targetFile,list<T> &targetList){
        string line;
        T object;
        stringstream iss(line);
        ifstream ifs(targetFile);
        if (!ifs.is_open())
            throw ios::failure("Archivo no encontrado");
        while(getline(ifs, line, '#')){
            if(line[0] == 0)
                continue;
            line.erase(0,2);
            iss >> object;
            targetList.push_back(object);
        }
    }
    template <class T>
    fstream& listTofile(list<T> &myList, fstream &myFStream){  // + Lista y archivo
        for(auto iterator = myList.begin();iterator != myList.end();iterator++)
            myFStream << "1*" << *iterator << '#';
        return myFStream;
    }
    void clear(){
        dataFileStream.open(dataFileDir,ios::out | ios::trunc);
        dataFileStream.close();
    }
    void compress(){

        list<Medico> myList;
        fileToList(dataFileDir,myList);
        listTofile(myList,dataFileStream);
    }
};
