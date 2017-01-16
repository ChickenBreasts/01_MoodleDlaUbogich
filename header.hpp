// plik naglowkowy, umieszczamy wszystko oprocz cial funkcji
#ifndef header_hpp
#define header_hpp

//ZMIENNE GLOBALNE

#include<string>
std::string sciezka;
std::string zalogowany;
int exitCode = 0;

//PROTOTYPY

void czyPierwszeUruchomienie(); //sprawdza czy program ma niezbedne pliki(czy to pierwsze uruchomienie), jak nie to je tworzy
void logowanie (); //DO UZUPELNIENIA pobiera dane do logowania i wpuszcza uzytkownika lub odrzuca
void rejestracja (); //pobiera dane uzytkowniów i odsyła do poczekalni
int ZliczanieWierszyPliku (string); //zlicza ilość wierszy pliku podanego w sciezce dostepu
void UsunKandydata (int nr_kandydata); //Usuwa wszystkie dane o kandydacie z poczekalni
void DopiszHaslo (int nr_kandydata); //Dopisuje nick i haslo kandydata do pliku hasla.txt
void DrukowanieKandydatow (); //wyswietla poczekalnie
void ZatwierdzanieKont (); // Pozwala na zatwierdzenie lub odrzucenie konta
void skrzynka(); //menu skrzynki ( pisanie wiadomosci, czytanie, wyjscie
void nowaWiadomosc(); //napisz nowa wiadomosc
void otrzymanaWiadomosc(); //czyta nowa wiadomosc
void ustawienia(); //pozwala na zobaczenie i zmiane niektoryc hdanych swojego konta
void ZalogowanyProfesor(); //DO UZUPELNIENIA  wyswietla menu dla profka
void ZalogowanyStudent(); // DO UZUPELNIENIAwyswietla medu studenta

#endif
