#ifndef SEM_ESTRUCTURAS_II_PACIENTES_H
#define SEM_ESTRUCTURAS_II_PACIENTES_H
#include "fecha.h"
#include "nombre.h"
#include "domicilio.h"
class Paciente{
private:
    string nss;
    Nombre nombre;
    Fecha fechaNacimiento;
    Domicilio domicilio;
    string numeroTelefono;
public:
    Paciente()= default;
    Paciente(const string &nss, const Nombre &nombre, const Fecha &fecha, const Domicilio &domicilio, const string &numeroTelefono){
        this->nss = nss;
        this->nombre = nombre;
        this->fechaNacimiento = fecha;
        this->domicilio = domicilio;
        this->numeroTelefono = stoi(numeroTelefono);
    }
    void setNSS(const string &nss){
        this->nss = nss;
    }
    void setNombre(const Nombre &nombre){
        this->nombre = nombre;
    }
    void setFechaNacimiento(const Fecha &fecha){
        this->fechaNacimiento = fecha;
    }
    void setDomicilio(const Domicilio &domicilio){
        this->domicilio = domicilio;
    }
    void setNumeroTelefono(const string &telefono){
        this->numeroTelefono = telefono;
    }

    [[nodiscard]] string getNSS() const{
        return this->nss;
    }
    [[nodiscard]] Nombre getNombre() const{
        return this->nombre;
    }
    [[nodiscard]] Fecha getFecha() const{
        return this->fechaNacimiento;
    }
    [[nodiscard]] Domicilio getDomicilio() const{
        return this->domicilio;
    }
    [[nodiscard]] string getTelefono() const{
        return this->numeroTelefono;
    }

    friend istream &operator >> (istream &ifs, Paciente &p){
        getline(ifs, p.nss,'*');
        ifs >> p.nombre >> p.fechaNacimiento;
        ifs >> p.domicilio;
        getline(ifs,p.numeroTelefono,'*');
        ifs.ignore();
        return ifs;
    }
    friend ostream &operator << (ostream &ofs, Paciente &p){
        ofs << p.nss <<'*'<< p.nombre << p.fechaNacimiento << p.domicilio << p.numeroTelefono <<'*';
        return ofs;
    }
    Paciente &operator = (const Paciente &p) = default;

    /*bool operator == (const Paciente &p){
        return this->nombre.apellidos == p.nombre.apellidos;
    }
    bool operator < (const Paciente &p){
        return this->nombre.apellidos < p.nombre.apellidos;
    }
    bool operator <= (const Paciente &p){
        return this->nombre.apellidos <= p.nombre.apellidos;
    }*/
};
#endif //SEM_ESTRUCTURAS_II_PACIENTES_H
