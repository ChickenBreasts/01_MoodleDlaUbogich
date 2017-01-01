//funkcje wspolne dla obu rodzajow uzytkownikow
#include "../header.hpp"
#include <windows.h>
#include <fstream>
#include <string>
using namespace std;

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

void rejestracja ()
{
    fstream sprawdzenie;
    fstream Do_zatwierdzenia;
    string nick,haslo1="1",haslo2="0"; //daje im rozne wartosci aby petla dzialala
    string imie,nazwisko;
    int indeks,wiek,nr_wiersza;
    string linia;

    cout<<"Podaj imie: "; cin>>imie;
    cout<<"Podaj nazwisko: "; cin>>nazwisko;
    cout<<"Podaj wiek: "; cin>>wiek;
    do{
    sprawdzenie.open("hasla.txt" , ios::in);
    nr_wiersza=1;
    cout<<"Podaj Nick do logowania: "; cin>>nick;                              // Sprawdzanie czy nick juz
        while(getline(sprawdzenie,linia)){                                     // przypadkiem nie jest w uzyciu
            if(nr_wiersza%2==1){
                if(linia==nick){
                    cout<<"Taki login juz istnieje!!! Sproboj ponownie."<<endl;
                    break;
                }
            }

            nr_wiersza++;
        }
    sprawdzenie.close();
    }while(nr_wiersza-1!=ZliczanieWierszyPliku());

    sprawdzenie.close();

    while(haslo1!=haslo2){
        cout<<"Podaj haslo: "; cin>>haslo1;
        cout<<"Powtorz haslo: "; cin>>haslo2;
        if(haslo1!=haslo2) cout<<"Powtorzone haslo jest rozne. Sproboj ponownie"<<endl;
    }

    Do_zatwierdzenia.open("usr//Do-zatwierdzenia", ios::out | ios::app);
    Do_zatwierdzenia <<imie<<endl<<nazwisko<<endl<<wiek<<endl<<nick<<endl<<haslo1;
    Do_zatwierdzenia.close();

    cout<<"Dziekujemy. Zgoszenie wyslano do weryfikacji."<<endl;
