// + Foolproof

#ifndef FARMAMANAGE_MAINUI_H
#define FARMAMANAGE_MAINUI_H
#include <string>
#include <iostream>
#include "medicUI.h"
#include "backupUI.h"
#include "consultsUI.h"
#include "drugsUI.h"
#include "patientUI.h"
#include "backupUI.h"
#include "diagnosisUI.h"

using std::string,std::cout,std::cin,std::endl,std::getline;
class MainUI{
public:
    void mainMenu(){
        system("cls");
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
        cout<<"|               FarmaManage                 |"<<'\n';
        cout<<"|              Menu principal               |"<<'\n';
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
        cout<<"|               1.-Medicos                  |"<<'\n';
        cout<<"|               2.-Pacientes                |"<<'\n';
        cout<<"|               3.-Diagnosticos             |"<<'\n';
        cout<<"|               4.-Medicamentos             |"<<'\n';
        cout<<"|               5.-Consultas                |"<<'\n';
        cout<<"|               6.-Respaldos                |"<<'\n';
        cout<<"|               0.-Salir                    |"<<'\n';
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
    }
    void run(){
        MedicUI medicUi;
        DrugsUI drugsUi;
        PatientUI patientUi;
        DiagnosisUI diagnosisUi;
        ConsultUI consultsUi;
        BackupsUI backupsUi;
        string opcion;
        int opcionInt = -1;
        mainMenu();
        do{
            cout<<"Ingrese opcion >> ";
            getline(cin,opcion,'\n');
            if(opcion.empty()) {
                cout << "Opcion invalida, intente de nuevo" << '\n';
                continue;
            }
            if(entradaValida(opcion)) {
                opcionInt = stoi(opcion);
            }
            else {
                cout << "Opcion invalida, intente de nuevo" << '\n';
                continue;
            }
            switch(opcionInt){
                case 0: // Exit
                    cout<<".:Vuelva pronto:.";
                    break;
                case 1: // Medic
                    system("cls");
                    medicUi.run();
                    mainMenu();
                    break;
                case 2: // Patient
                    system("cls");
                    patientUi.run();
                    mainMenu();
                    break;
                case 3: // Diagnosis
                    diagnosisUi.run();
                    mainMenu();
                    break;
                case 4: // Medicamentos
                    drugsUi.run();
                    mainMenu();
                    break;
                case 5: // Consults
                    consultsUi.run();
                    mainMenu();
                    break;
                case 6: // Backups
                    backupsUi.run();
                    mainMenu();
                    break;
                default:
                    cout<<"Opcion invalida, intente de nuevo"<<'\n';
            }
        }while(opcionInt != 0);
        system("cls");
    }
    bool entradaValida(string &str){
        return isNumeric(str);
    }
    // Función de utilidad para comprobaciones
    bool isNumeric(const string &str){
        // Regresa verdadero si todos los caracteres de la cadena son numéricos
        return all_of(str.begin(),str.end(),::isdigit);
    }
};
#endif //FARMAMANAGE_MAINUI_H
