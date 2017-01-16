//glowna petla programu

#include "header.hpp"

int main() {
    while (exitCode = 0) {
        int menu;

        czyPierwszeUruchomienie();

        cout<< "OPCJE: ";
        cout<< "1-Logowanie";
        cout<< "2-Rejestracja";
        cout<< "3-Wyjscie"<<endl;
        cin>>menu;

        switch (menu) {
        case 1:
            logowanie();
        break;
        case 2:
            rejestracja();
        break;
        case 3:
            exitCode++;
        break;
        }
    }
  return 0;
}
