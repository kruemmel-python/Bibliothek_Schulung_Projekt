#include "Terminal.hpp"
#include <iostream>

Terminal::Terminal(Bibliothek& bibliothek) : bibliothek(bibliothek) {}

void Terminal::start() {
    int auswahl = 0;
    while (auswahl != 7) {  // Menüpunkte bis 7
        zeigeMenue();
        std::cin >> auswahl;
        verarbeiteEingabe(auswahl);
    }
}

void Terminal::zeigeMenue() const {
    
    std::cout << "Bibliothek-Terminal" << std::endl;
    std::cout << "1. Medien auflisten" << std::endl;
    std::cout << "2. Nutzer auflisten" << std::endl;
    std::cout << "3. Medien aus CSV laden" << std::endl;
    std::cout << "4. Nutzer aus CSV laden" << std::endl;
    std::cout << "5. Medium hinzufügen" << std::endl;  // Neuer Menüpunkt
    std::cout << "6. Nutzer hinzufügen" << std::endl;  // Neuer Menüpunkt
    std::cout << "7. Beenden" << std::endl;
    std::cout << "Auswahl: ";
}

void Terminal::verarbeiteEingabe(int auswahl) {
    switch (auswahl) {
    case 1:
        bibliothek.listeMedien();
        break;
    case 2:
        bibliothek.listeNutzer();
        break;
    case 3:
        bibliothek.ladeMedienAusCSV();
        break;
    case 4:
        bibliothek.ladeNutzerAusCSV();
        break;
    case 5:
        mediumHinzufuegen();  // Medium hinzufügen
        break;
    case 6:
        nutzerHinzufuegen();  // Nutzer hinzufügen
        break;
    case 7:
        std::cout << "Beenden..." << std::endl;
        break;
    default:
        std::cout << "Ungültige Auswahl. Bitte erneut versuchen." << std::endl;
    }
}

void Terminal::mediumHinzufuegen() {
    std::string typ, autor, titel, kategorie, code;
    std::cout << "Medientyp (Buch/CD/DVD): ";
    std::cin >> typ;
    std::cout << "Autor: ";
    std::cin >> autor;
    std::cout << "Titel: ";
    std::cin >> titel;
    std::cout << "Kategorie: ";
    std::cin >> kategorie;
    std::cout << "Code: ";
    std::cin >> code;

    bibliothek.fuegeMediumHinzu(typ, autor, titel, kategorie, code);
}

void Terminal::nutzerHinzufuegen() {
    std::string vorname, nachname, strasse, plz, ort, email, telefonnummer, mitgliedsnummer;
    int hausnummer;
    std::cout << "Vorname: ";
    std::cin >> vorname;
    std::cout << "Nachname: ";
    std::cin >> nachname;
    std::cout << "Strasse: ";
    std::cin >> strasse;
    std::cout << "Hausnummer: ";
    std::cin >> hausnummer;
    std::cout << "PLZ: ";
    std::cin >> plz;
    std::cout << "Ort: ";
    std::cin >> ort;
    std::cout << "Email: ";
    std::cin >> email;
    std::cout << "Telefonnummer: ";
    std::cin >> telefonnummer;
    std::cout << "Mitgliedsnummer: ";
    std::cin >> mitgliedsnummer;

    bibliothek.fuegeNutzerHinzu(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);
}
