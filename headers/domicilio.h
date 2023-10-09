#ifndef SEM_ESTRUCTURAS_II_DOMICILIO_H
#define SEM_ESTRUCTURAS_II_DOMICILIO_H
#include <string>
#include <fstream>
using namespace std;
class Domicilio{
private:
    string calle;
    int numero;
    string colonia;
    int codigoPostal;
    string municipio;
public:
    Domicilio()= default;
    Domicilio(const string &calle, const string &numero, const string &colonia, const string &codigoPostal, const string &municipio){
        this->calle = calle;
        this->numero = stoi(numero);
        this->colonia = colonia;
        this->codigoPostal = stoi(codigoPostal);
        this->municipio = municipio;
    }
    void setCalle(const string &calle){
        this->calle = calle;
    };
    void setNumero(const int &numero){
        this->numero = numero;
    };
    void setcolonia(const string &colonia){
        this->colonia = colonia;
    };
    void setCodigoPostal(const int &codigoPostal){
        this->codigoPostal = codigoPostal;
    };
    void setMunicipio(const string &municipio){
        this->municipio = municipio;
    };
    string getCalle(){
        return this->calle;
    }
    short int getNumero(){
        return this->numero;
    }
    string getColonia(){
        return this->colonia;
    }
    short int getCodigoPostal(){
        return this->codigoPostal;
    }
    string getMunicipio(){
        return this->municipio;
    }

    friend istream &operator >> (istream&ifs, Domicilio &d){
        getline(ifs,d.calle,'*');
        ifs>> d.numero;
        ifs.ignore(1,'*');
        getline(ifs, d.colonia,'*');
        ifs>> d.codigoPostal;
        ifs.ignore();
        getline(ifs, d.municipio,'*');
        return ifs;
    }
    friend ostream &operator << (ostream &ofs,Domicilio &d){
        ofs << d.calle <<'*'<< d.numero <<'*'<< d.colonia <<'*'<< d.codigoPostal <<'*'<< d.municipio<<'*';
        return ofs;
    }
};
#endif //SEM_ESTRUCTURAS_II_DOMICILIO_H
