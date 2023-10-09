#ifndef SEM_ESTRUCTURAS_II_DIAGNOSTICO_H
#define SEM_ESTRUCTURAS_II_DIAGNOSTICO_H
#include <fstream>
#include <string>
using namespace std;
class Diagnostico{
private:
    string codigo;
    string descripcion;
    string indicacionesTerap;
public:
    Diagnostico()= default;
    Diagnostico(const string &codigo, const string &desc, const string &indicaciones){
        this->codigo = codigo;
        this->descripcion =  desc;
        this->indicacionesTerap = indicaciones;
    }
    [[nodiscard]] string getCodigo() const{
        return this->codigo;
    }
    [[nodiscard]] string getDescripcion() const{
        return this->descripcion;
    }
    [[nodiscard]] string getIndicaciones() const{
        return this->indicacionesTerap;
    }
    void setCodigo(const string &code) {
        this->codigo = code;
    }
    void setDescripcion(const string &desc){
        this->descripcion = desc;
    }
    void setIndicaciones(const string &indic){
        this->indicacionesTerap = indic;
    }

    friend ostream &operator << (ostream &ofs, Diagnostico &d){
        ofs << d.codigo <<'*'<< d.descripcion <<'*'<< d.indicacionesTerap<<'*';
        return ofs;
    }
    friend istream &operator >> (istream &ifs, Diagnostico &d){
        getline(ifs, d.codigo,'*');
        getline(ifs, d.descripcion,'*');
        getline(ifs, d.indicacionesTerap,'*');
        return ifs;
    }
    Diagnostico &operator = (const Diagnostico &d) = default;

    bool operator < (const Diagnostico &d){
        return this->codigo < d.codigo;
    }
    bool operator <= (const Diagnostico &d){
        return this->codigo <= d.codigo;
    }
    bool operator == (const Diagnostico &d){
        return this->codigo == d.codigo;
    }

};
#endif //SEM_ESTRUCTURAS_II_DIAGNOSTICO_H
