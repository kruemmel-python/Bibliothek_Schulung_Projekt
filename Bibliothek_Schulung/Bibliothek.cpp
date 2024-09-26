#include "Bibliothek.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include "Medien.hpp"
#include "Nutzer.hpp"
#include "CSVHandler.hpp"
#include "Buch.hpp"
#include "CD.hpp"
#include "DVD.hpp"
#include "Datenbankverbindung.hpp"
#include <stdexcept>

using namespace std;  // Du kannst hier `using namespace std;` verwenden

// Konstruktor, initialisiert die Verbindung zur Datenbank
Bibliothek::Bibliothek(const string& dbName) : db(dbName) {
    if (!db.isConnected()) {
        throw runtime_error("Fehler: Keine Verbindung zur Datenbank.");
    }
}

// Medien aus der CSV-Datei laden
void Bibliothek::ladeMedienAusCSV() {
    auto data = CSVHandler::readCSV(medienCSV);
    for (const auto& row : data) {
        if (row.size() < 7) continue; // Mindestens 7 Spalten erwartet

        string typ = row[0];
        string autor = row[1];
        string titel = row[2];
        string kategorie = row[4];
        string code = row[5];

        if (code.empty()) {
            cerr << "Fehler: Medientyp " << typ << " hat keinen Code." << endl;
            continue;
        }

        if (typ == "Buch") {
            medien.push_back(make_shared<Buch>(autor, titel, kategorie, code));
        }
        else if (typ == "CD") {
            medien.push_back(make_shared<CD>(autor, titel, kategorie, code));
        }
        else if (typ == "DVD") {
            medien.push_back(make_shared<DVD>(autor, titel, kategorie, code));
        }
    }
}

// Nutzer aus der CSV-Datei laden
void Bibliothek::ladeNutzerAusCSV() {
    auto data = CSVHandler::readCSV(nutzerCSV);

    bool ersteZeileIstUeberschrift = true;  // Falls die erste Zeile Überschriften enthält
    for (const auto& row : data) {
        if (ersteZeileIstUeberschrift) {
            ersteZeileIstUeberschrift = false;
            continue;  // Überspringe die erste Zeile
        }

        if (row.size() < 9) continue; // Mindestens 9 Spalten erwartet

        string vorname = row[0];
        string nachname = row[1];
        string strasse = row[2];
        int hausnummer = 0;
        string plz = row[4];
        string ort = row[5];
        string email = row[6];
        string telefonnummer = row[7];
        string mitgliedsnummer = row[8];

        // Fehlerbehandlung für ungültige Hausnummer
        try {
            hausnummer = stoi(row[3]); // Versuche, die Hausnummer zu konvertieren
        }
        catch (const invalid_argument& e) {
            cerr << "Ungültige Hausnummer für Nutzer mit Mitgliedsnummer: " << mitgliedsnummer << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cerr << "Hausnummer außerhalb des Bereichs für Nutzer mit Mitgliedsnummer: " << mitgliedsnummer << endl;
            continue;
        }

        // Wenn alles gültig ist, füge den Nutzer hinzu
        nutzer.emplace_back(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);
    }
}

// Medien in die CSV-Datei speichern
void Bibliothek::speichereMedienInCSV() {
    vector<vector<string>> data;
    for (const auto& m : medien) {
        data.push_back({ m->getTyp(), m->getAutor(), m->getTitel(), "", m->getKategorie(), m->getCode(), "", "" });
    }
    CSVHandler::writeCSV(medienCSV, data);
}

// Nutzer in die CSV-Datei speichern
void Bibliothek::speichereNutzerInCSV() {
    vector<vector<string>> data;
    for (const auto& n : nutzer) {
        data.push_back({ n.getVorname(), n.getNachname(), n.getStrasse(), to_string(n.getHausnummer()),
                        n.getPLZ(), n.getOrt(), n.getEmail(), n.getTelefonnummer(), n.getMitgliedsnummer() });
    }
    CSVHandler::writeCSV(nutzerCSV, data);
}

// Medien in die Datenbank speichern
void Bibliothek::speichereMedienInDatenbank() {
    if (!db.isConnected()) {
        cerr << "Fehler: Keine Verbindung zur Datenbank." << endl;
        return;
    }
    for (const auto& m : medien) {
        string query = "INSERT INTO Medien (Typ, Autor, Titel, Kategorie, Code) VALUES ('" +
            m->getTyp() + "', '" + m->getAutor() + "', '" + m->getTitel() + "', '" +
            m->getKategorie() + "', '" + m->getCode() + "');";
        try {
            db.executeQuery(query);
        }
        catch (const exception&) {
            cerr << "Fehler beim Speichern des Mediums in die Datenbank." << endl;
        }
    }
}

// Nutzer in die Datenbank speichern
void Bibliothek::speichereNutzerInDatenbank() {
    if (!db.isConnected()) {
        cerr << "Fehler: Keine Verbindung zur Datenbank." << endl;
        return;
    }
    for (const auto& n : nutzer) {
        string query = "INSERT INTO Nutzer (Vorname, Nachname, Strasse, Hausnummer, PLZ, Ort, Email, Telefonnummer, Mitgliedsnummer) VALUES ('" +
            n.getVorname() + "', '" + n.getNachname() + "', '" + n.getStrasse() + "', " +
            to_string(n.getHausnummer()) + ", '" + n.getPLZ() + "', '" + n.getOrt() + "', '" +
            n.getEmail() + "', '" + n.getTelefonnummer() + "', '" + n.getMitgliedsnummer() + "');";
        try {
            db.executeQuery(query);
        }
        catch (const exception&) {
            cerr << "Fehler beim Speichern des Nutzers in die Datenbank." << endl;
        }
    }
}

// Medien in der Konsole auflisten (mit verbesserter Formatierung)
void Bibliothek::listeMedien() const {
    cout << "Liste der Medien:" << endl;
    cout << "-----------------" << endl;
    for (const auto& m : medien) {
        cout << "Typ: " << m->getTyp()
            << " | Autor: " << m->getAutor()
            << " | Titel: " << m->getTitel()
            << " | Kategorie: " << m->getKategorie()
            << " | Code: " << m->getCode()
            << endl;
    }
    cout << "-----------------" << endl;
}

// Nutzer in der Konsole auflisten (mit verbesserter Formatierung)
void Bibliothek::listeNutzer() const {
    cout << "Liste der Nutzer:" << endl;
    cout << "-----------------" << endl;
    for (const auto& n : nutzer) {
        cout << "Vorname: " << n.getVorname()
            << " | Nachname: " << n.getNachname()
            << " | Strasse: " << n.getStrasse()
            << " | Hausnummer: " << n.getHausnummer()
            << " | PLZ: " << n.getPLZ()
            << " | Ort: " << n.getOrt()
            << " | Email: " << n.getEmail()
            << " | Telefonnummer: " << n.getTelefonnummer()
            << " | Mitgliedsnummer: " << n.getMitgliedsnummer()
            << endl;
    }
    cout << "-----------------" << endl;
}

// Neue Methode: Medium hinzufügen
void Bibliothek::fuegeMediumHinzu(const string& typ, const string& autor, const string& titel, const string& kategorie, const string& code) {
    // Medium zur internen Liste hinzufügen
    if (typ == "Buch") {
        medien.push_back(make_shared<Buch>(autor, titel, kategorie, code));
    }
    else if (typ == "CD") {
        medien.push_back(make_shared<CD>(autor, titel, kategorie, code));
    }
    else if (typ == "DVD") {
        medien.push_back(make_shared<DVD>(autor, titel, kategorie, code));
    }

    // Medium zur CSV-Datei hinzufügen
    vector<vector<string>> data = {
        { typ, autor, titel, "", kategorie, code, "", "" }
    };
    CSVHandler::writeCSVAppend(medienCSV, data);

    // Medium in die Datenbank speichern, falls vorhanden
    if (db.isConnected()) {
        string query = "INSERT INTO Medien (Typ, Autor, Titel, Kategorie, Code) VALUES ('" +
            typ + "', '" + autor + "', '" + titel + "', '" + kategorie + "', '" + code + "');";
        try {
            db.executeQuery(query);
        }
        catch (const exception& e) {
            cerr << "Fehler beim Hinzufügen des Mediums zur Datenbank: " << e.what() << endl;
        }
    }
}

// Neue Methode: Nutzer hinzufügen
void Bibliothek::fuegeNutzerHinzu(const string& vorname, const string& nachname, const string& strasse, int hausnummer, const string& plz, const string& ort, const string& email, const string& telefonnummer, const string& mitgliedsnummer) {
    // Nutzer zur internen Liste hinzufügen
    nutzer.emplace_back(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);

    // Nutzer zur CSV-Datei hinzufügen
    vector<vector<string>> data = {
        { vorname, nachname, strasse, to_string(hausnummer), plz, ort, email, telefonnummer, mitgliedsnummer }
    };
    CSVHandler::writeCSVAppend(nutzerCSV, data);

    // Nutzer in die Datenbank speichern, falls vorhanden
    if (db.isConnected()) {
        string query = "INSERT INTO Nutzer (Vorname, Nachname, Strasse, Hausnummer, PLZ, Ort, Email, Telefonnummer, Mitgliedsnummer) VALUES ('" +
            vorname + "', '" + nachname + "', '" + strasse + "', " + to_string(hausnummer) + ", '" + plz + "', '" + ort + "', '" +
            email + "', '" + telefonnummer + "', '" + mitgliedsnummer + "');";
        try {
            db.executeQuery(query);
        }
        catch (const exception& e) {
            cerr << "Fehler beim Hinzufügen des Nutzers zur Datenbank: " << e.what() << endl;
        }
    }
}
