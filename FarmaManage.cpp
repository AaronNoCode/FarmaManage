#include "UI/mainUI.h"
#include <clocale>

int main(){
    setlocale(LC_CTYPE,"Spanish");
    MainUI ui;
    ui.run();
    cout<<"         .:Vuelva pronto:.\n";
    system("pause");
    return 0;
}
