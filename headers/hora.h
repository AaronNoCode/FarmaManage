#ifndef SEM_ESTRUCTURAS_II_HORA_H
#define SEM_ESTRUCTURAS_II_HORA_H
#include <fstream>
using namespace std;
class Hora{
private:
    short int horas;
    short int minutos;
public:
    Hora() = default;
    Hora(const string &s){
        this->horas = stoi(s.substr(0,2));
        this->minutos = stoi(s.substr(3,2));
    }
    Hora(short int horas, short int minutos){
        this->horas = horas;
        this->minutos = minutos;
    }
    [[nodiscard]] int getHoras() const{
        return this->horas;
    }
    [[nodiscard]] int getMinutos() const{
        return this->minutos;
    }

    void setHoras(short int h){
        this->horas = h;
    }
    void setMinutos(short int m){
        this->minutos = m;
    }

    friend istream &operator >> (istream&ifs,Hora&h){
        ifs >> h.horas;
        ifs.ignore(1,':');
        ifs >> h.minutos;
        ifs.ignore(1,'*');
        return ifs;
    }
    friend ostream &operator << (ostream&ofs,Hora&h){
        ofs << h.horas << '*' <<h.minutos<<'*';
        return ofs;
    }

    Hora& operator = (const Hora &h)= default; //! Checar si sirve bien dejándolo como default
    bool operator < (const Hora &h) const{
        return ((this->horas < h.horas) && (this->minutos < h.minutos));
    }
    bool operator <= (const Hora &h) const{
        return ((this->horas <= h.horas) && (this->minutos <= h.minutos));

    }
    bool operator >= (const Hora &h) const{
        return ((this->horas >= h.horas) && (this->minutos >= h.minutos));
    }
    bool operator == (const Hora &h) const{
        return ((this->horas == h.horas) && (this->minutos == h.minutos));
    }
};

#endif //SEM_ESTRUCTURAS_II_HORA_H
