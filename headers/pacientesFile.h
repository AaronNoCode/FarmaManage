#ifndef SEM_ESTRUCTURAS_II_PACIENTESFILE_H
#define SEM_ESTRUCTURAS_II_PACIENTESFILE_H
#include <fstream>
#include <list>
#include <string>
#include <iostream>
#include "indextuple.h"
class ArchivoPacientes{
private:
    fstream dataFile;
    fstream indexFile;
    fstream indexByNameFile;

    /*list<Pacientes> dataList;*/
    list<IndexTuple<>> indexByNameList;
    list<IndexTuple<string>> indexList;

    void reindex();
    void compress();

    template<class T>
    list<IndexTuple<T>>& fileToList(fstream&, list<T>&);

    template<class T>
    fstream& listToFile(list<IndexTuple<T>>&,fstream&);


    int getIndex(const string&) const; // + Busca por código. Lo manda a llamar find data y busca en la lista invertida, tiene de parámetro un código o nombre
    int getIndexByName(const Name&) const; // + Busca por nombre


public:
    ArchivoPacientes();
    ~ArchivoPacientes();
    void addData(const Pacientes&);
    void addData(const list<Pacientes>&);
    void delData(const int&);
    int findData(const Pacientes&); // + Buscar por estructura
    int findData(const string&); // + Buscar por código
    int findData(const Name&); // + Buscar por nombre

    list<Pacientes> toList() const;

    void clear();
    // + Editar es una mezcla de agregar y eliminar, que es borrar lo que haya escrito y luego volver a meter algo.
    // + Eliminar recibe un entero y busca ese índice.
    // + Localizar recibe un "Pacientesor" y regresa un índice.
};
#endif //SEM_ESTRUCTURAS_II_PACIENTESFILE_H
