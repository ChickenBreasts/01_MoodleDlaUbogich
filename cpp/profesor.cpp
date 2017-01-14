//funkcje uzywane jedynie przez profesora
#include "../header.hpp"
#include <iostream>

using namespace std;
void ZalogowanyProfesor ()
{
    int opcja;
    while(true){
    cout<<"Witaj Profesorze W Moodle dla biednych!"<<endl;
    cout<<"OPCJE:"<<endl<<"1-Poczta 2-Kursanci 3-kalendarz 4-ustawienia"<<endl;
    cout<<"Wybierz Opcje: ";cin>>opcja;
    switch(opcja){
        case 1: //skrzynka();
            break;
        case 2: //kursanci();
            break;
        case 3: //kalendarz();
            break;
        case 4: //ustawienia();
            break;
        default: cout<<"Zla opcja!!! Sprobuj jeszcze raz.";break;
        }
    }

}
