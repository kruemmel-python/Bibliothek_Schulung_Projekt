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

    // Funktionen zum Hinzufügen, Entfernen und Suchen
    void mediumHinzufuegen();
    void nutzerHinzufuegen();
    void mediumEntfernen();
    void nutzerEntfernen();
    void sucheMedien();
    void sucheNutzer();
    void sucheRegal();  // Neu: Regal suchen und Bücher anzeigen

    Bibliothek& bibliothek;
};

#endif // TERMINAL_HPP
