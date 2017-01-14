//funkcje uzywane jedynie przez student
#include "../header.hpp"
#include <iostream>

using namespace std;
void ZalogowanyStudent ()
{
    int opcja;
    while(true){
    cout<<"Witaj Studencie W Moodle dla biednych!"<<endl;
    cout<<"OPCJE:"<<endl<<"1-Poczta 2-Studia 3-kalendarz 4-ustawienia"<<endl;
    cout<<"Wybierz Opcje: ";cin>>opcja;
    switch(opcja){
        case 1: //skrzynka();
            break;
        case 2:
            cout<<"OPCJE: 1-Moje oceny 2-Inni Studenci"<<endl;
            cout<<"Wybierz Opcje:";
                cin>>opcja;
                while(true){
                if(opcja==1) {
                    //ocenyStudent();
                }else if(opcja==2){
                    //kursanci();
                }else cout<<"Zla opcja!!! Sproboj jeszcze raz.";
                }
            break;
        case 3: //kalendarz();
            break;
        case 4: //ustawienia();
            break;
        default: cout<<"Zla opcja!!! Sproboj jeszcze raz.";break;
        }
    }

}
