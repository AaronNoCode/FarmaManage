#ifndef SEM_ESTRUCTURAS_II_MEDICAMENTO_H
#define SEM_ESTRUCTURAS_II_MEDICAMENTO_H
#include <fstream>
#include <cstring>
using namespace std;
class Medicamento{
private:
    string codigoMedicamento;
    string nombreMedicamento;
public:
    Medicamento()= default;
    Medicamento(const string &codigo, const string &nombre){
        this->codigoMedicamento = codigo;
        this->nombreMedicamento = nombre;
    }
    void setCodigo(const string &codigo){
        this->codigoMedicamento = codigo;
    }
    void setNombre(const string &nombre){
        this->nombreMedicamento = nombre;
    }
    [[nodiscard]] string getCodigo() const{
        return this->codigoMedicamento;
    }
    [[nodiscard]] string getNombre() const{
        return this->nombreMedicamento;
    }

    friend ostream &operator << (ostream &ofs, Medicamento &m){ //! Editar porque este dato es el que termina el registro
        ofs << m.codigoMedicamento <<'*'<< m.nombreMedicamento << '*';
        return ofs;
    }
    friend istream &operator >> (istream &ifs, Medicamento &m){
        getline(ifs, m.codigoMedicamento,'*');
        getline(ifs, m.nombreMedicamento,'*');
        return ifs;
    }
    Medicamento &operator = (const Medicamento &m) = default;

    bool operator == (const Medicamento &m) const{
        return this->nombreMedicamento == m.nombreMedicamento;
    }
    bool operator < (const Medicamento &m) const{
        return this->nombreMedicamento < m.nombreMedicamento;
    }
    bool operator <= (const Medicamento &m) const{
        return this->nombreMedicamento <= m.nombreMedicamento;
    }
};
#endif //SEM_ESTRUCTURAS_II_MEDICAMENTO_H
