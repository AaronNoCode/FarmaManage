#ifndef SEM_ESTRUCTURAS_II_NOMBRE_H
#define SEM_ESTRUCTURAS_II_NOMBRE_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;
class Nombre{
private:
    string nombre;
    string apellido;
public:
    Nombre()= default;
    Nombre(const string& nombres, const string& apellidos){
        istringstream iss(nombres);
        iss >> nombre;
        istringstream iss2(apellidos);
        iss2 >> apellido;
    }

    [[nodiscard]] string getNombre() const{
        return (this->nombre);
    }
    [[nodiscard]] string getApellidos() const{
        return (this->apellido);
    }

    void setApellidos(const string &apellidos){
        istringstream iss(apellidos);
        iss >> apellido;
    }
    void setNombres(const string &nombres){
        istringstream iss(nombres);
        iss >> nombre;
    }

    string toString(){
        string str = nombre + " " + apellido;
        for (char& i : str){
            i = toupper(i);
        }
        return str;
    }

    friend istream &operator >> (istream&ifs,Nombre&n){
        getline(ifs, n.apellido, '*');
        getline(ifs, n.nombre, '*');
        return ifs;
    }
    friend ostream &operator << (ostream&ofs,Nombre&n){
        ofs << n.apellido << '*' << n.nombre << '*';
        return ofs;
    }
    Nombre &operator = (const Nombre &n){
        this->nombre = n.nombre;
        this->apellido = n.apellido;
    }

   bool operator == (const Nombre &n){
        return (this->apellido == n.apellido);
    }
    bool operator <= (Nombre &n){
        return this->toString() <= n.toString();
    }
    bool operator < (Nombre &n){
        return this->toString() < n.toString();
    }

    friend class Paciente;
    friend class Medico;
};
#endif //SEM_ESTRUCTURAS_II_NOMBRE_H
