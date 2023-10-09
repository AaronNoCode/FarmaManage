#ifndef SEM_ESTRUCTURAS_II_FECHA_H
#define SEM_ESTRUCTURAS_II_FECHA_H
#include <fstream>
#include <string>
using namespace std;
class Fecha{
private:
    int dia;
    int mes;
    int anio;
public:
    Fecha()= default;
    Fecha(const string &s){
        this->dia = stoi(s.substr(0,2));
        this->mes = stoi(s.substr(3,2));
        this->anio = stoi(s.substr(6,4));
    }
    Fecha(const short int &dia, const short int &mes, const short int &anio){
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    }
    void setDia(const short int &dia){
        this->dia = dia;
    }
    void setMes(const short int &mes){
        this->mes = mes;
    }
    void setAnio(const short int &anio){
        this->anio = anio;
    }
    [[nodiscard]] short int getDia() const{
        return this->dia;
    }
    [[nodiscard]] short int getMes() const{
        return this->mes;
    }
    [[nodiscard]] short int getAnio() const{
        return this->anio;
    }

    friend ostream &operator << (ostream &ofs,Fecha &f){
        ofs << f.dia <<'/'<< f.mes <<'/'<< f.anio <<'*';
        return ofs;
    }
    friend istream &operator >> (istream &ifs,Fecha &f){
        ifs >> f.dia;
        ifs.ignore(1, '/');
        ifs >> f.mes;
        ifs.ignore(1, '/');
        ifs >> f.anio;
        ifs.ignore();
        return ifs;
    }
    Fecha& operator = (const Fecha &f)= default; //! Checar si sirve bien este operador al declararlo default
    bool operator == (const Fecha &f) const{
        return ((this->dia == f.dia) && (this->mes == f.mes) && (this->anio == f.anio));
    }

    bool operator < (const Fecha &f) const{
        return ((this->anio < f.anio) && (this->mes < f.mes) && (this->dia < f.dia));
    }

    bool operator <= (const Fecha &f) const{
        return ((this->anio <= f.anio) && (this->mes <= f.mes) && (this->dia <= f.dia));
    }

    bool operator >= (const Fecha &f) const{
        return ((this->anio >= f.anio) && (this->mes >= f.mes) && (this->dia >= f.dia));
    }
};
#endif //SEM_ESTRUCTURAS_II_FECHA_H
