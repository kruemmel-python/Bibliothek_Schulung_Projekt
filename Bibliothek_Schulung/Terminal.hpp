#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "Bibliothek.hpp"

class Terminal {
public:
    Terminal(Bibliothek& bibliothek);

    void start();

private:
    void zeigeMenue() const;
    void verarbeiteEingabe(int auswahl);

    void mediumHinzufuegen();  // Funktion zum Hinzuf�gen eines Mediums
    void nutzerHinzufuegen();  // Funktion zum Hinzuf�gen eines Nutzers

    Bibliothek& bibliothek;
};

#endif // TERMINAL_HPP
