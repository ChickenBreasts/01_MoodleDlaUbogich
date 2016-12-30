//funkcje wspolne dla obu rodzajow uzytkownikow
#include "../header.hpp"
#include <windows.h>
#include <fstream>

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
