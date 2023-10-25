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
        importFromBackup("backups/archivo_consultas.file");
        populateListAndFiles();
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
    void importFromBackup(const string& targetFile){
        ifstream ifs(targetFile,ios::in);
        ofstream ofs(dataFileDir,ios::out | ios::trunc);
        if (!ifs.is_open())
            throw ios::failure("Respaldo no encontrado");
        list<Medico> listMedic;
        Consulta c;
        string aux;
        while(!ifs.eof()){
            getline(ifs,aux,'#');
            stringstream iss(aux);
            iss >> c;
            listMedic.push_back(c.getMedico());
        }
        listMedic.sort();
        listMedic.unique();
        for (auto &iterator : listMedic){
            ofs << "1*" << iterator << '#';
        }
    }

    void addData(Medico &m){
        IndexTuple<Nombre> tupleName;
        IndexTuple<string> tupleCode;
        long long index, buscado;
        fstream ofs(dataFileDir, ios::out | ios::in);
        // Si encuentra el nombre en la lista, checa si el registro está dado de alta (checa en archivo el estado (0 o 1)) y si está inactivo, cambia el 0 por un 1
        buscado = findDataByName(m.getNombre());
        if(buscado != -1){
            ofs.seekp(buscado);
            // TODO pedir confirmación para reactivarlo
            ofs.put('1');
            return;
        }
        ofs.seekp(0,ios::end);
        index = ofs.tellp();
        ofs << "1*" << m << '#';
        // Se llena la tupla de código con el médico obtenido del string stream y se agrega a la lista correspondiente
        tupleCode.setIndex(index);
        tupleCode.setData(m.getCodigoEmpleado());
        listIdxCode.push_front(tupleCode);

        // Se llena la tupla de nombre con el médico obtenido del string stream y se agrega a la lista correspondiente
        tupleName.setIndex(index);
        tupleName.setData(m.getNombre());
        listIdxName.push_front(tupleName);

        listIdxCode.sort();
        listIdxName.sort();

        // Grabanado a archivo de índice CÓDIGO
        idxCodeStream.open(idxCodeDir,ios::out | ios::trunc);
        if (!idxCodeStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-code'");
        listTofile(listIdxCode,idxCodeStream);
        idxCodeStream.close();

        // Grabando a archivo de índice NOMBRE
        idxNameStream.open(idxNameDir,ios::out | ios::trunc);
        if (!idxNameStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-name'");
        listTofile(listIdxName,idxNameStream);
        idxNameStream.close();
    }
    // + Nota, siempre debe estar poblada la lista para poder buscar
    int findDataByName(Nombre name) const{ // * DONE
        for(auto const &iterator : listIdxName){
            if(iterator.getData() == name)
                return iterator.getIndex();
        }
        // Si el ciclo se termina y no encontró el objeto, retorna -1
            return -1;
    }
    // + Nota, siempre debe estar poblada la lista para poder buscar
    int findDataByCode(string &code) const{ // * DONE
        for(const auto &iterator :listIdxCode){
            if(iterator.getData() == code)
                return iterator.getIndex();
        }
        // Si el ciclo se termina y no encontró el objeto, retorna -1
            return -1;
    }
    Medico retrieve(int &idx){ // * DONE
        for(auto const &iterator :listIdxCode){
            if(iterator.getIndex() == idx){
                dataFileStream.open(dataFileDir,ios::in);
                if(!dataFileStream.is_open())
                    throw ios::failure("Archivo no encontrado 'medicos-file'");
                dataFileStream.clear();
                dataFileStream.seekg(idx,ios::beg);
                string dirtyLine, cleanLine;
                Medico med;
                getline(dataFileStream, dirtyLine,'#');
                cout<<dirtyLine;
                if(dirtyLine[0] == '0')
                    throw ios::failure("Indice eliminado");
                cleanLine = dirtyLine.substr(2);
                stringstream iss(cleanLine);
                iss>>med;
                dataFileStream.close();
                return med;
            }
        }
        throw ios::failure("Indice no existe");
    }
    // + Siempre lee el archivo de médicos y actualiza las listas
    void populateListAndFiles(){
        list<IndexTuple<Nombre>> myListTupleName;
        list<IndexTuple<string>> myListTupleCode;
        IndexTuple<Nombre> tupleName;
        IndexTuple<string> tupleCode;
        string dirtyLine, cleanLine;
        long long index;
        Medico m;
        Nombre nombreAux;
        dataFileStream.open(dataFileDir,ios::in);
        if (!dataFileStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-file'");
        // Ciclo para leer todos los médicos del archivo de médicos
        while(getline(dataFileStream, dirtyLine, '#')){
            // Sacar el índice del puntero de lectura para su posición
            index = dataFileStream.tellg();
            if(dirtyLine.empty())
                continue;
            // Si el booleano que indica si el índice está activo es cero, se ignora
            if(dirtyLine[0] == '0')
                continue;
            // Se limpia la línea quitándole el booleano y el separador de campo
            cleanLine = dirtyLine.substr(2);
            // Creación de un string stream con la línea limpia
            stringstream iss(cleanLine);
            // El stream se mete a médico
            iss >> m;
            // Limpieza del stream
            iss.clear();

            // Se llena la tupla de código con el médico obtenido del string stream y se agrega a la lista correspondiente
            tupleCode.setIndex(index);
            tupleCode.setData(m.getCodigoEmpleado());
            myListTupleCode.push_back(tupleCode);

            // Se llena la tupla de nombre con el médico obtenido del string stream y se agrega a la lista correspondiente
            tupleName.setIndex(index);
            tupleName.setData(m.getNombre());
            myListTupleName.push_back(tupleName);
        }
        dataFileStream.close();
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
        idxCodeStream.close();

        // Grabando a archivo de índice NOMBRE
        idxNameStream.open(idxNameDir,ios::out | ios::trunc);
        if (!idxNameStream.is_open())
            throw ios::failure("Archivo no encontrado 'medicos-name'");
        listTofile(myListTupleName,idxNameStream);
        idxNameStream.close();

        fileToList(idxNameDir,listIdxName);
        fileToList(idxCodeDir,listIdxCode);
    }
    void delData(int &idx){
        for(auto const &iterator : listIdxCode){
            if(iterator.getIndex() == idx){
                dataFileStream.seekp(iterator.getIndex());
                dataFileStream.put('0');
                populateListAndFiles();
                dataFileStream.close();
                return;
                // TODO checar si sirve así
            }
        }
        throw ios::failure("Indice inexistente");
    }
    void delData(Nombre& nombre){
        for(auto const &iterator :listIdxName){
            if(iterator.getData() == nombre){
                dataFileStream.seekp(iterator.getIndex());
                dataFileStream.put('0');
                populateListAndFiles();
                dataFileStream.close();
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
                populateListAndFiles();
                dataFileStream.close();
                return;
                // TODO checar si sirve así
            }
        }
    }
    // + Lista exclusiva para médico
    template <class T>
    void fileToList(const string &targetFile,list<T> &targetList){
        string dirtyLine, cleanLine;
        T object;
        ifstream ifs(targetFile,ios::in);
        if (!ifs.is_open())
            throw ios::failure("Archivo no encontrado");
        while(getline(ifs, dirtyLine, '#')){
            if(dirtyLine.empty())
                continue;
            if(dirtyLine[0] == 0)
                continue;
            cleanLine = dirtyLine.substr(2);
            stringstream iss(cleanLine);
            iss >> object;
            targetList.push_back(object);
            iss.clear();
        }
        ifs.close();
    }
    template <typename T>
    void listTofile(list<T> &myList, fstream &myFStream){// + Lista y archivo
        for(auto &iterator : myList)
            myFStream << "1*" << iterator << '#';
        // Se asegura de que se estriba en el disco
    }
    void clear(){
        dataFileStream.open(dataFileDir,ios::out | ios::trunc);
        dataFileStream.close();
    }
    void compress(){
        list<Medico> myList;
        fileToList(dataFileDir,myList);
        listTofile(myList,dataFileStream);
        dataFileStream.close();
    }
};
