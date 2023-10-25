#ifndef SEM_ESTRUCTURAS_II_CONSULTAS_H
#define SEM_ESTRUCTURAS_II_CONSULTAS_H
#include <fstream>
#include "hora.h"
#include "medicos.h"
#include "fecha.h"
#include "pacientes.h"
#include "diagnostico.h"
#include "medicamento.h"
class Consulta{
private:
    Fecha fecha;
    Hora hora;
    Diagnostico diagnostico;
    Medico medico;
    Paciente paciente;
    Medicamento medicamento1;
    Medicamento medicamento2;
    Medicamento medicamento3;
public:
    Consulta() = default;
    Consulta(Fecha &fecha, Hora &hora, Diagnostico &diagnostico, Medico &medico, Paciente &paciente, Medicamento &medicamento1, Medicamento &medicamento2, Medicamento &medicamento3){
        this->fecha = fecha;
        this->hora = hora;
        this->diagnostico = diagnostico;
        this->medico = medico;
        this->paciente = paciente;
        this->medicamento1 = medicamento1;
        this->medicamento2 = medicamento2;
        this->medicamento3 = medicamento3;
    }

    [[nodiscard]] Fecha getFecha() const{
        return this->fecha;
    }
    [[nodiscard]] Hora getHora() const{
        return this->hora;
    }
    [[nodiscard]] Diagnostico getDiagnostico() const{
        return this->diagnostico;
    }
    [[nodiscard]] Medico getMedico() const{
        return this->medico;
    }
    [[nodiscard]] Paciente getPaciente() const{
        return this->paciente;
    }
    [[nodiscard]] Medicamento getMedicamento1() const{
        return this->medicamento1;
    }
    [[nodiscard]] Medicamento getMedicamento2() const{
        return this->medicamento2;
    }
    [[nodiscard]] Medicamento getMedicamento3() const{
        return this->medicamento3;
    }

    void setFecha(const Fecha &fecha){
        this->fecha = fecha;
    }
    void setHora(const Hora &hora){
        this->hora = hora;
    }
    void setDiagnostico(const Diagnostico &diagnostico){
        this->diagnostico = diagnostico;
    }
    void setMedico(const Medico &medico){
        this->medico = medico;
    }
    void setPaciente(const Paciente &paciente){
        this->paciente = paciente;
    }
    void setMedicamento1(const Medicamento &medicamento){
        this->medicamento1 = medicamento;
    }
    void setMedicamento2(const Medicamento &medicamento){
        this->medicamento2 = medicamento;
    }
    void setMedicamento3(const Medicamento &medicamento){
        this->medicamento3 = medicamento;
    }

    friend ostream&operator << (ostream &ofs,Consulta &c){
        ofs << c.fecha << c.hora << c.diagnostico << c.medico << c.paciente << c.medicamento1 << c.medicamento2 << c.medicamento3 <<'#';
        return ofs;
    }
    friend istream&operator >> (istream &ifs,Consulta &c){
        ifs >> c.fecha >> c.hora >> c.diagnostico >> c.medico >> c.paciente >> c.medicamento1 >> c.medicamento2 >> c.medicamento3;
        ifs.ignore();
        return ifs;
    }
    Consulta &operator = (const Consulta &c){
        if(&c == this)
            return *this;
        this->fecha = c.fecha;
        this->hora = c.hora;
        this->diagnostico = c.diagnostico;
        this->medico = c.medico;
        this->paciente = c.paciente;
        this->medicamento1 = c.medicamento1;
        this->medicamento2 = c.medicamento2;
        this->medicamento3 = c.medicamento3;
        return *this;
    }

    bool operator != (Consulta &c){
        return (this->fecha != c.fecha);
    }
    bool operator == (const Consulta &c){
        return (this->fecha == c.fecha) && (this->diagnostico == c.diagnostico);
    }
    bool operator < (const Consulta &c){
        return this->fecha < c.fecha;
    }
    bool operator <= (const Consulta &c){
        return this->fecha <= c.fecha;
    }

};
#endif //SEM_ESTRUCTURAS_II_CONSULTAS_H
