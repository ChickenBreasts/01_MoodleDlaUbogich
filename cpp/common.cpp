//funkcje wspolne dla obu rodzajow uzytkownikow
#include "../header.hpp"
#include <windows.h>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

void czyPierwszeUruchomienie()
{
    fstream kalendarz;
    kalendarz.open("kalendarz.txt");
    if(kalendarz.is_open()) //jesli kalendarz instnieje to go zamykamy
    {
        kalendarz.close();
    }
    else //jesli nie istnieje to tworzymy strukture katalogow i plikow(zamykamy je)
    {
        CreateDirectory(("usr"), NULL);
        CreateDirectory(("usr\\prof"), NULL);

        ofstream kalendarz ("kalendarz.txt");
        kalendarz.close();
        ofstream hasla ("hasla.txt");
        hasla.close();
        ofstream do_zatwierdzenia ("usr\\do_zatwierdzenia.txt");
        do_zatwierdzenia.close();
        ofstream ustawienia ("usr\\prof\\ustawienia.txt");
        ustawienia.close();

        fstream hasla;
        hasla.open("hasla.txt", fstream::out);
        hasla << "profesor"<<endl;
        hasla << "profesor2"<<endl;
        hasla.close();
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

void nowaWiadomosc() //WYMAGA ZMIAN SCIEZKI
{
  string odbiorcy, tresc, tytul;
  int licznik = 0;
  cout << "Podaj odbiorce(numer indeksu) : ";
  getline(cin, odbiorcy);
  std::cout << "Tytul: ";
  getline(cin, tytul);
  std::cout << "Tresc: ";
  getline(cin,tresc);

  string path = "usr/" + odbiorcy+ "/nowa.txt"; //ZMIEN DLA WINDOWSA

  fstream nowa;
  nowa.open(path, ios::out | ios::app);
    nowa << "Tytul: " << tytul << endl;
    nowa << "Tresc: " << tresc << endl;
    nowa << "Podpis: " << zalogowany << endl;
  nowa.close();
}

void otrzymanaWiadomosc() //WYMAGA ZMIAN SCIEZKI
{
  string path1 = "usr/" + zalogowany + "/nowa.txt";
  string tytul, tresc, podpis, wiersz,path2;
  fstream nowa;
  nowa.open(path1, ios::in | ios::out);
  if (!nowa.good()) {
    std::cout << "Nie masz nowych wiadomosci :(" << endl;
    return false;
  }
  else
  {
    getline(nowa, tytul);
    getline(nowa, tresc);
    getline(nowa, podpis);
  }
  std::cout << "Tytul: " << tytul << endl;
  std::cout << "Tresc: " << tresc << endl;
  std::cout << "Podpis: " << podpis << endl;

  ofstream tmp("usr/" + zalogowany + "/tmp.txt");
  tmp.close();
  tmp.open("usr/" + zalogowany + "/tmp.txt", ios::in);
  while(getline(nowa, wiersz)) {
    tmp << wiersz << endl;
  }
  tmp.close();
  nowa.close();
  remove(path1.c_str());
  path2="usr/" + zalogowany + "/tmp.txt";
  rename(path2.c_str(),path1.c_str());
}

void skrzynka()
{
  int petlaSkrzynki=0,wybor;
  std::cout << "Jestes w swojej skrzynce." << endl;
  std::cout << "Wpisz: " << endl;
  std::cout << "1.Napisz nowa wiadomosc." << endl;
  std::cout << "2.Przeczytaj nowa wiadomosc." << endl;
  std::cout << "3.Wroc do poprzedniego menu." << endl;
  do {
    cin>>wybor;
    switch (wybor) {
      case 1:
        nowaWiadomosc();
      case 2:
        otrzymanaWiadomosc();
      case 3:
        petlaSkrzynki++;
    }
  } while(petlaSkrzynki==0);
}

void ustawienia()
{
    fstream ustawienia;
    string linia;
    int opcja;
    int wiersz=1;
    while(true)
    {
    cout<<"OPCJE: 1-Zobacz swoje dane 2-Zmien dane 3-Powrot do menu"<<endl;
    cout<<"Wybierz opcje: ";
    cin>>opcja;
    if(opcja==1){
        ustawienia.open("ustawienia.txt", ios::in);
        while(getline(ustawienia,linia)){

        switch(wiersz){

        case 1: cout<<"Nick: "; break;
        case 2: cout<<"Imie i Nazwisko: "; break;
        case 3: cout<<"Mail: "; break;
        case 4: cout<<"Status: "; break;
        case 5: cout<<"Indeks: "; break;
        default: break;

        }
        cout<<linia<<endl;
        wiersz++;
        }
        wiersz=1;
        ustawienia.close();
    }else if(opcja==2){
        string zmiana;
        fstream nowe;
        int nr_wiersza;
        cout<<"Co chcesz zmienic? 1-Login 2-Mail"<<endl;
        cout<<"Wybierz opcje: ";
        cin>>opcja;
            switch (opcja){
                case 1:{
                    nr_wiersza=1;
                    ustawienia.open("ustawienia.txt" , ios::in);
                    nowe.open("nowe.txt", ios::out);
                    cout<<"Podaj nowy Nick: ";
                    cin>>zmiana;
                    while(getline(ustawienia,linia)){
                        if(nr_wiersza==1) {
                                nowe<<zmiana<<endl;
                        }else nowe<<linia<<endl;
                        nr_wiersza++;
                    }
                    ustawienia.close();
                    nowe.close();
                    remove("ustawienia.txt");
                    rename("nowe.txt","ustawienia.txt");
                    break;
                }
                case 2:{
                    ustawienia.open("ustawienia.txt" , ios::in);
                    nr_wiersza=1;
                    nowe.open("nowe.txt", ios::out);
                    cout<<"Podaj nowy Mail: ";
                    cin>>zmiana;
                    while(getline(ustawienia,linia)){
                        if(nr_wiersza==3) {
                                nowe<<zmiana<<endl;
                        }else nowe<<linia<<endl;
                        nr_wiersza++;
                    }
                    ustawienia.close();
                    nowe.close();
                    remove("ustawienia.txt");
                    rename("nowe.txt","ustawienia.txt");
                    break;
                }
                default: break;
        }


    }else if(opcja==3){

        cout<<"Zostaniesz Przeniesiony do menu.";
        //zalogowany student profesor
        break;
    }else cout<<"Nie wlasciwa opcja!!! Sproboj jeszcze raz."<<endl;
    }

}
