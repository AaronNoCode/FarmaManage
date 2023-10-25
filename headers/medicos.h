#ifndef SEM_ESTRUCTURAS_II_MEDICOS_H
#define SEM_ESTRUCTURAS_II_MEDICOS_H
#include <iostream>
#include <string>
#include "nombre.h"
#include "hora.h"
class Medico{
private:
    string codigoEmpleado;
    Nombre nombre;
    string cedula;
    Hora horaEntrada;
    Hora horaSalida;
public:
    Medico()= default;
    Medico(const string &codigoEmpleado, const Nombre& nombre, const string& cedula, Hora horaEntrada, Hora horaSalida){
        this->codigoEmpleado = codigoEmpleado;
        this->nombre = nombre;
        this->cedula = cedula;
        this->horaEntrada = horaEntrada;
        this->horaSalida = horaSalida;
    }
    void setCodigoEmpleado(string &codigoEmpleado){
        this->codigoEmpleado = codigoEmpleado;
    }
    void setNombre(const string &nombre, const string &apellidos){
        this->nombre.setNombres(nombre);
        this->nombre.setApellidos(apellidos);
    }
    void setCedula(const string &cedula){
        this->cedula = cedula;
    }
    void setHoraEntrada(const short int &horasEntrada, const short int &minutosEntrada){
        this->horaEntrada.setHoras(horasEntrada);
        this->horaEntrada.setMinutos(minutosEntrada);
    }
    void setHoraSalida(const short int &horasSalida, const short int &minutosSalida){
        this->horaSalida.setHoras(horasSalida);
        this->horaSalida.setMinutos(minutosSalida);
    }
    [[nodiscard]] string getCodigoEmpleado() const{
        return this->codigoEmpleado;
    }
    [[nodiscard]] Nombre getNombre() const{
        return this->nombre;
    }
    [[nodiscard]] string getCedula() const{
        return this->cedula;
    }
    [[nodiscard]] Hora getHoraEntrada() const{
        return this->horaEntrada;
    }
    [[nodiscard]] Hora getHoraSalida() const{
        return this->horaSalida;
    }

    friend istream &operator >> (istream&ifs,Medico&m){
        string primerApellido, segundoApellido, primerNombre, segundoNombre,cedula;
        getline(ifs, m.codigoEmpleado,'*');
        ifs >>m.nombre;
        getline(ifs,m.cedula,'*');
        ifs >> m.horaEntrada >> m.horaSalida;
        ifs.ignore();
        return ifs;
    }
    friend ostream &operator << (ostream&ofs,Medico&m){
        ofs << m.codigoEmpleado <<'*'<< m.nombre << m.cedula <<'*'<< m.horaEntrada << m.horaSalida;
        return ofs;
    }
    Medico &operator = (Medico m) {
        if(&m == this)
            return *this;
        this->codigoEmpleado = m.codigoEmpleado;
        this->nombre = m.nombre;
        this->cedula = m.cedula;
        this->horaEntrada = m.horaEntrada;
        this->horaSalida = m.horaSalida;
        return *this;
    }
    bool operator != (Medico &m) {
        return this->nombre != m.nombre;
    }
    bool operator == (Medico &m) {
        return this->nombre == m.nombre;
    }
    bool operator >= (Medico &m) {
        return this->nombre >= m.nombre;
    }
    bool operator > (Medico &m) {
        return this->nombre > m.nombre;
    }
    bool operator < (Medico &m) {
        return this->nombre < m.nombre;
    }
    bool operator <= (Medico &m) {
        return this->nombre <= m.nombre;
    }
};

#endif //SEM_ESTRUCTURAS_II_MEDICOS_H
