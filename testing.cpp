#include <iostream>
#include <fstream>
#include <sstream>
#include "headers/consultas.h"
#include "sources/medicos-file.h"
using namespace std;

int main(){
    /*try{
         ifstream fileIn("backups/archivo_consultas.file", ios::in);
        ofstream fileOut("backups/medicos-file.txt", ios::out | ios::trunc);
        if(fileOut.fail() || fileIn.fail()){
            throw runtime_error("Failed");
        }
        
        Consulta c;
        Medico m;
        string line;
        while (getline(fileIn,line,'#')){
            istringstream iss(line);
            iss >> c;
            m = c.getMedico();
            fileOut << "1*"<< m <<'#';
            cout<<c.getPaciente().getNombre().getNombre()<< '\n';
        }
        cout<<"open";
        fileIn.close();
    }catch (const runtime_error &e){
        cout << "No se pudo abrir" << e.what() << endl;
    } */
        MedicosFile MF;
        cout<< MF.reindex(); 




    return 0;
}




/* * ios::trunc limpia el archivo antes de insertar lo que sea en el archivo
 * Destructor en las clases de archivos que cierre los archivos pertenecientes
 * Validar 0/1 de si es registro activo al pasar de archivo a lista (o no si es que se comprime (eliminar registros inactivos) al cerrar el archivo o en cada eliminación).
 * La lista es un template porque se van a guardar objetos dentro de ella
 *
 *
 * */
