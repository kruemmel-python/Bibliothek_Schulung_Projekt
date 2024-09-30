#include "Terminal.hpp"
#include <iostream>

using namespace std;

// Konstruktor
Terminal::Terminal(Bibliothek& bibliothek) : bibliothek(bibliothek) {}

void Terminal::start() {
    int auswahl = 0;
    while (auswahl != 12) {
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
    cout << "5. Medium hinzufügen" << endl;
    cout << "6. Nutzer hinzufügen" << endl;
    cout << "7. Medium entfernen" << endl;
    cout << "8. Nutzer entfernen" << endl;
    cout << "9. Medien suchen" << endl;
    cout << "10. Nutzer suchen" << endl;
    cout << "11. Regal suchen und Bücher anzeigen" << endl;  // Neu
    cout << "12. Beenden" << endl;
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
        mediumHinzufuegen();
        break;
    case 6:
        nutzerHinzufuegen();
        break;
    case 7:
        mediumEntfernen();
        break;
    case 8:
        nutzerEntfernen();
        break;
    case 9:
        sucheMedien();
        break;
    case 10:
        sucheNutzer();
        break;
    case 11:
        sucheRegal();  // Neu
        break;
    case 12:
        cout << "Beenden..." << endl;
        break;
    default:
        cout << "Ungültige Auswahl. Bitte erneut versuchen." << endl;
    }
}

// Neue Methode: Regal suchen und Bücher anzeigen
void Terminal::sucheRegal() {
    string regName;
    cout << "Geben Sie den Namen des Regals ein: ";
    cin >> regName;
    bibliothek.zeigeBuecherInRegal(regName);
}

// Methode: Medium hinzufügen
void Terminal::mediumHinzufuegen() {
    string typ, autor, titel, kategorie, code, regal;
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
    cout << "Regal: ";
    cin >> regal;

    bibliothek.fuegeMediumHinzu(typ, autor, titel, kategorie, code, regal);
}

// Methode: Nutzer hinzufügen
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

// Methode: Medium entfernen
void Terminal::mediumEntfernen() {
    string code;
    cout << "Geben Sie den Code des Mediums ein, das Sie entfernen möchten: ";
    cin >> code;

    if (bibliothek.entferneMedium(code)) {
        cout << "Medium erfolgreich entfernt." << endl;
    }
    else {
        cout << "Medium mit Code " << code << " nicht gefunden." << endl;
    }
}

// Methode: Nutzer entfernen
void Terminal::nutzerEntfernen() {
    string mitgliedsnummer;
    cout << "Geben Sie die Mitgliedsnummer des Nutzers ein, den Sie entfernen möchten: ";
    cin >> mitgliedsnummer;

    if (bibliothek.entferneNutzer(mitgliedsnummer)) {
        cout << "Nutzer erfolgreich entfernt." << endl;
    }
    else {
        cout << "Nutzer mit Mitgliedsnummer " << mitgliedsnummer << " nicht gefunden." << endl;
    }
}

// Methode: Medien suchen
void Terminal::sucheMedien() {
    string kriterium, suchbegriff;
    cout << "Nach welchem Kriterium möchten Sie suchen? (Autor/Titel/Kategorie): ";
    cin >> kriterium;
    cout << "Suchbegriff: ";
    cin >> suchbegriff;

    auto ergebnisse = bibliothek.sucheMedien(suchbegriff, kriterium);

    if (ergebnisse.empty()) {
        cout << "Keine Medien gefunden." << endl;
    }
    else {
        for (const auto& medium : ergebnisse) {
            cout << "Typ: " << medium->getTyp()
                << " | Autor: " << medium->getAutor()
                << " | Titel: " << medium->getTitel()
                << " | Kategorie: " << medium->getKategorie()
                << " | Code: " << medium->getCode() << endl;
        }
    }
}

// Methode: Nutzer suchen
void Terminal::sucheNutzer() {
    string kriterium, suchbegriff;
    cout << "Nach welchem Kriterium möchten Sie suchen? (Vorname/Nachname): ";
    cin >> kriterium;
    cout << "Suchbegriff: ";
    cin >> suchbegriff;

    auto ergebnisse = bibliothek.sucheNutzer(suchbegriff, kriterium);

    if (ergebnisse.empty()) {
        cout << "Keine Nutzer gefunden." << endl;
    }
    else {
        for (const auto& nutzer : ergebnisse) {
            cout << "Vorname: " << nutzer.getVorname()
                << " | Nachname: " << nutzer.getNachname()
                << " | Strasse: " << nutzer.getStrasse()
                << " | Hausnummer: " << nutzer.getHausnummer()
                << " | PLZ: " << nutzer.getPLZ()
                << " | Ort: " << nutzer.getOrt()
                << " | Email: " << nutzer.getEmail()
                << " | Telefonnummer: " << nutzer.getTelefonnummer()
                << " | Mitgliedsnummer: " << nutzer.getMitgliedsnummer() << endl;
        }
    }
}
