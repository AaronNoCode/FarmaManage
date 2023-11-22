#ifndef FARMAMANAGE_MEDICUI_H
#define FARMAMANAGE_MEDICUI_H
#include <iostream>
#include "../headers/medicos-file.h"
#include "../headers/color.hpp"
using std::string,std::cout,std::cin,std::getline;
class MedicUI{
public:
    void menu(){
        system("cls");
        cout << dye::light_yellow("+++++++++++++++++++++++++++++++++++++++++++++") << '\n';
        cout << dye::light_yellow("|              ")<<dye::light_blue("FarmaManage")<<dye::light_yellow("                  |") << '\n';
        cout << dye::light_yellow("|              ")<<dye::light_blue("Menu Medicos")<<dye::light_yellow("                 |") << '\n';
        cout << dye::light_yellow("+++++++++++++++++++++++++++++++++++++++++++++") << '\n';
        cout << dye::light_yellow("|             1.-Crear nuevo                |") << '\n';
        cout << dye::light_yellow("|             2.-Buscar medico              |") << '\n';
        cout << dye::light_yellow("|             3.-Editar medico              |") << '\n';
        cout << dye::light_yellow("|             4.-Eliminar medico            |") << '\n';
        cout << dye::light_yellow("|             0.-Menu principal             |") << '\n';
        cout << dye::light_yellow("+++++++++++++++++++++++++++++++++++++++++++++") << '\n';
    }
    bool entradaNumValida(string &str){
        return isNumeric(str);
    }
    bool confirmacion(){
        string opcion;
        int opcionInt = 0;
        cout << dye::light_blue("\t\t\t¿Los datos son correctos?\n\t\t\t1.-Sí\n\t\t\t2.-No")<<dye::light_green("\n$ ");
        do {
            cout << dye::light_green("\n$ ");
            getline(cin, opcion, '\n');
            if(opcion.empty()){
                cout << dye::red("             Opcion invalida, intente de nuevo");
                continue;
            }
            if (entradaNumValida(opcion)){
                cout << dye::red("\t\t\tNo se admiten caracteres especiales ni alfabeticos, intente de nuevo");
                continue;
            }else{
                opcionInt = stoi(opcion);
                if(opcionInt > 2 || opcionInt < 1){
                    cout << dye::red("             Opcion invalida, intente de nuevo");
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
            cout << dye::light_green("\n$ ");
            getline(cin,opcion,'\n');
            if(opcion.empty()){
                cout << dye::red("             Opcion invalida, intente de nuevo");
                continue;
            }
            if(entradaNumValida(opcion)) {
                opcionInt = stoi(opcion);
            }else {
                cout << dye::red("             Opcion invalida, intente de nuevo");
                continue;
            }
            switch(opcionInt){
                case 0: // Vuelve a menú principal
                    break;
                case 1: // Crear nuevo
                    system("cls");
                    menu();
                    break;
                case 2: // Buscar
                    system("cls");
                    menu();
                    break;
                case 3: // Editar
                    system("cls");
                    menu();
                    break;
                case 4: // Eliminar
                    system("cls");
                    menu();
                    break;
                default:
                    cout << dye::red("             Opcion invalida, intente de nuevo");
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
