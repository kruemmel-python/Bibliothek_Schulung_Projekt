#include "Terminal.hpp"
#include <iostream>

using namespace std;

Terminal::Terminal(Bibliothek& bibliothek) : bibliothek(bibliothek) {}

void Terminal::start() {
    int auswahl = 0;
    while (auswahl != 7) {  // Menüpunkte bis 7
        zeigeMenue();
        cin >> auswahl;
        verarbeiteEingabe(auswahl);
    }
}

void Terminal::zeigeMenue() const {
    cout << "Bibliothek-Terminal" << endl;
    cout << "1. Medien auflisten" << endl;
    cout << "2. Nutzer auflisten" << endl;
    cout << "3. Medien aus CSV laden" << endl;
    cout << "4. Nutzer aus CSV laden" << endl;
    cout << "5. Medium hinzufügen" << endl;  // Neuer Menüpunkt
    cout << "6. Nutzer hinzufügen" << endl;  // Neuer Menüpunkt
    cout << "7. Beenden" << endl;
    cout << "Auswahl: ";
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
        cout << "Beenden..." << endl;
        break;
    default:
        cout << "Ungültige Auswahl. Bitte erneut versuchen." << endl;
    }
}

void Terminal::mediumHinzufuegen() {
    string typ, autor, titel, kategorie, code;
    cout << "Medientyp (Buch/CD/DVD): ";
    cin >> typ;
    cout << "Autor: ";
    cin >> autor;
    cout << "Titel: ";
    cin >> titel;
    cout << "Kategorie: ";
    cin >> kategorie;
    cout << "Code: ";
    cin >> code;

    bibliothek.fuegeMediumHinzu(typ, autor, titel, kategorie, code);
}

void Terminal::nutzerHinzufuegen() {
    string vorname, nachname, strasse, plz, ort, email, telefonnummer, mitgliedsnummer;
    int hausnummer;
    cout << "Vorname: ";
    cin >> vorname;
    cout << "Nachname: ";
    cin >> nachname;
    cout << "Strasse: ";
    cin >> strasse;
    cout << "Hausnummer: ";
    cin >> hausnummer;
    cout << "PLZ: ";
    cin >> plz;
    cout << "Ort: ";
    cin >> ort;
    cout << "Email: ";
    cin >> email;
    cout << "Telefonnummer: ";
    cin >> telefonnummer;
    cout << "Mitgliedsnummer: ";
    cin >> mitgliedsnummer;

    bibliothek.fuegeNutzerHinzu(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);
}
