//funkcje wspolne dla obu rodzajow uzytkownikow
#include "../header.hpp"
#include <windows.h>
#include <fstream>
#include <string>

void czyPierwszeUruchomienie()
{
    std::fstream kalendarz;
    kalendarz.open("kalendarz.txt");
    if(kalendarz.is_open()) //jesli kalendarz instnieje to go zamykamy
    {
        kalendarz.close();
    }
    else //jesli nie istnieje to tworzymy strukture katalogow i plikow(zamykamy je)
    {
        CreateDirectory(("usr"), NULL);
        CreateDirectory(("usr\\prof"), NULL);
        CreateDirectory(("usr\\prof\\mail"), NULL);
        std::ofstream kalendarz ("kalendarz.txt");
        kalendarz.close();
        std::ofstream hasla ("hasla.txt");
        hasla.close();
        std::ofstream do_zatwierdzenia ("usr\\do_zatwierdzenia.txt");
        do_zatwierdzenia.close();
        std::ofstream ustawienia ("usr\\prof\\ustawienia.txt");
        ustawienia.close();
    }
}
using namespace std;
void logowanie ()
{
    int numer_wiersza=1;
    fstream log; //plik do logowania
    string nick , haslo;
    string Nick_Z_Pliku , Haslo_Z_Pliku;
    string linia; //linia pliku

    cout<<"Podaj nick: "; cin>>nick;
    cout<<"Podaj haslo: "; cin>>haslo;

    log.open("hasla.txt" , ios::in);
    if(log.good()){
        while(getline(log,linia)){
            switch (numer_wiersza%2)                  // wpisywanie nieparzystych linii
            {                                         // pliku jako nicki i parzystych
                case 1: Nick_Z_Pliku = linia; break;  // jako hasla
                case 0: Haslo_Z_Pliku = linia; break;
            }
            if(nick==Nick_Z_Pliku && haslo==Haslo_Z_Pliku){
                cout<<"zalogowany"<<endl;              // tutaj trzeba wsadzic fukcje
                break;                                 // ktora umieszcza uzytkownika w menu itp
            }
            numer_wiersza++;
        }

    }
    log.close();
    if(numer_wiersza==ZliczanieWierszyPliku()+1)
    {
        cout<<"bledne haslo lub nick!!! sproboj jeszcze raz"<<endl;
        logowanie();
    }
}
