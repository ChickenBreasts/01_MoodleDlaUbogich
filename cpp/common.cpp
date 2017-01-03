//funkcje wspolne dla obu rodzajow uzytkownikow
#include "../header.hpp"
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdio>
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
}

int ZliczanieWierszyPliku (string sciezka)
{
    fstream plik;
    int ilosc_wierszy=0;
    string linia;
    plik.open( sciezka.c_str(),  ios::in);
    while(getline(plik,linia)){
        ilosc_wierszy++;
    }

    return ilosc_wierszy;
}

void UsunKandydata (int nr_kandydata)
{
    fstream Do_zatwierdzenia, nowe;
    string linia;
    int nr_wiersza=1;
    Do_zatwierdzenia.open("usr//Do-zatwierdzenia.txt", ios::in);
    nowe.open("usr//dupa.txt", ios::out );
    while(getline(Do_zatwierdzenia,linia)){
        if(nr_wiersza>(5*nr_kandydata) || nr_wiersza<=(nr_kandydata*5)-5){ // wybiera wszystko oprocz kandydata
            nowe<<linia<<endl;
        }
        nr_wiersza++;
    }
    Do_zatwierdzenia.close();
    nowe.close();
    remove("usr//Do-zatwierdzenia.txt");
    rename("usr//dupa.txt" , "usr//Do-zatwierdzenia.txt");

}

void DopiszHaslo (int nr_kandydata)
{
    fstream hasla;
    fstream Do_zatwierdzenia;
    string nick,haslo,linia;
    int nr_wiersza=1;

    Do_zatwierdzenia.open("usr//Do-zatwierdzenia.txt",ios::in);

    while(getline(Do_zatwierdzenia,linia)){
        if(nr_wiersza==(5*nr_kandydata)-1){
            nick=linia;
        }if(nr_wiersza==5*nr_kandydata){
            haslo=linia;
            break;
        }

            nr_wiersza++;
    }
    Do_zatwierdzenia.close();

    hasla.open("hasla.txt", ios::app);

    hasla<<nick<<endl;
    hasla<<haslo<<endl;

}

void DrukowanieKandydatow ()
{
    fstream dane_kandydatow;
    int nr_wiersza=1;
    string linia;
    dane_kandydatow.open("usr//Do-zatwierdzenia.txt" , ios::in);  //drukuje kandydatow na ekran

    while (getline(dane_kandydatow,linia)){
        if(nr_wiersza%5==1) cout<<"Kandydat numer: "<<nr_wiersza/5+1<<endl;
        cout<<linia<<endl;
        nr_wiersza++;
    }
    dane_kandydatow.close();
}

void ZatwierdzanieKont ()
{
    fstream dane_kandydatow;
    int nr_wiersza=1,opcja,nr_kandydata;
    string linia;

    while(true){
    cout<<"OPCJE: 1-zatwierdz 2-odrzuc 3-wyswietl kandydatow 4-wyjdz"<<endl;
    cout<<"Wybierz opcje: "; cin>>opcja;
    if(opcja==1){
        cout<<"Podaj numer kandydata do zatwierdzenia: ";
        cin>>nr_kandydata;

            DopiszHaslo(nr_kandydata);
            UsunKandydata(nr_kandydata);

    }else if(opcja==2){
        cout<<"Podaj numer kandydata do odrzucenia: ";
        cin>>nr_kandydata;

            UsunKandydata(nr_kandydata);         

    }else if(opcja==3){
        DrukowanieKandydatow();
    }else if(opcja==4) cout<<"Zostaniesz przeniesiony do menu"<<endl;  //w tym miejscu damy fukcje ktora przenosi do menu
    else cout<<"Nie wlasciwa opcja. Sprobuj jeszcze raz!"<<endl;
    }
}
