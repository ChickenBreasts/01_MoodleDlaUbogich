//funkcje uzywane jedynie przez profesora
#include "../header.hpp"
#include <iostream>

using namespace std;
void ZalogowanyProfesor () //DO UZUPELNIENIA
{
    int opcja;
    while(true){
    cout<<"Witaj Profesorze W Moodle dla biednych!"<<endl;
    cout<<"OPCJE:"<<endl<<"1-Poczta 2-Kursanci 3-kalendarz 4-ustawienia 5-wyloguj"<<endl;
    cout<<"Wybierz Opcje: ";cin>>opcja;
    switch(opcja){
        case 1: skrzynka();
            break;
        case 2: //kursanci();
            break;
        case 3: //kalendarz();
            break;
        case 4: ustawienia();
            break;
        case 5: exitCode=1;
        default: cout<<"Zla opcja!!! Sprobuj jeszcze raz.";break;
        }
    }

}
