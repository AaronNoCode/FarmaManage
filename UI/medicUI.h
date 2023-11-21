#ifndef FARMAMANAGE_MEDICUI_H
#define FARMAMANAGE_MEDICUI_H
#include <iostream>
#include "../headers/medicos-file.h"
using std::string,std::cout,std::cin,std::getline;
class MedicUI{
public:
    void menu(){
        system("cls");
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
        cout<<"|              FarmaManage                  |"<<'\n';
        cout<<"|              Menu medicos                 |"<<'\n';
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
        cout<<"|            1.-Crear nuevo                 |"<<'\n';
        cout<<"|            2.-Buscar medico               |"<<'\n';
        cout<<"|            3.-Editar medico               |"<<'\n';
        cout<<"|            4.-Eliminar medico             |"<<'\n';
        cout<<"|            0.-Menu principal              |"<<'\n';
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<'\n';
    }
    bool entradaNumValida(string &str){
        return isNumeric(str);
    }
    bool confirmacion(){
        string opcion;
        int opcionInt = 0;
        cout<<"\t\t\t¿Los datos son correctos?\n\t\t\t1.-Sí\n\t\t\t2.-No\n>> ";
        do {
            getline(cin, opcion, '\n');
            if(opcion.empty()){
                cout << "\t\t\tOpcion invalida, intente de nuevo\n>> ";
                continue;
            }
            if (entradaNumValida(opcion)){
                cout << "\t\t\tNo se admiten caracteres especiales ni alfabeticos, intente de nuevo\n>> ";
                continue;
            }else{
                opcionInt = stoi(opcion);
                if(opcionInt > 2 || opcionInt < 1){
                    cout << "\t\t\tOpcion invalida, intente de nuevo\n>> ";
                }
            }
        }while(opcionInt > 2 || opcionInt < 1);

        return opcionInt == 1;
    }
    void run(){
        MedicosFile mf;
        Medico m;
        string opcion;
        int opcionInt = 99;
        menu();
        do{
            cout<<"Ingrese opcion >> ";
            getline(cin,opcion,'\n');
            if(opcion.empty()){
                cout<<"Opcion invalida, intente de nuevo"<<'\n';
                continue;
            }
            if(entradaNumValida(opcion)) {
                opcionInt = stoi(opcion);
            }
            else {
                cout<<"Opcion invalida, intente de nuevo"<<'\n';
                continue;
            }
            switch(opcionInt){
                case 0: // Vuelve a menú principal
                    break;
                case 1: // Crear nuevo

                    system("cls");
                    break;
                case 2: // Buscar
                    system("cls");
                    break;
                case 3: // Editar
                    system("cls");
                    break;
                case 4: // Eliminar
                    system("cls");
                    break;
                default:
                    cout<<"Opcion invalida, intente de nuevo"<<'\n';
            }
        }while(opcionInt != 0);
    }
    void insertar(){

    }
    void buscar(){

    }
    void editar(){

    }
    void eliminar(){

    }
    // Función de utilidad para comprobaciones
    bool isNumeric(const string &str){
        // Regresa verdadero si todos los caracteres de la cadena son numéricos
        return all_of(str.begin(),str.end(),::isdigit);
    }
};
#endif //FARMAMANAGE_MEDICUI_H
