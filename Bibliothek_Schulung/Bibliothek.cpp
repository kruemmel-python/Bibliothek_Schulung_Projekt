#include "Bibliothek.hpp"
#include "Buch.hpp"
#include "CD.hpp"
#include "DVD.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>  // Für std::string::find Methode

using namespace std;



// Standardkonstruktor (falls erforderlich)
Bibliothek::Bibliothek() : db("default.db") {
    if (!db.isConnected()) {
        throw runtime_error("Fehler: Keine Verbindung zur Datenbank.");
    }
    regale.emplace_back("Regal A", 10);  // Erstelle ein Regal mit dem Namen "Regal A" und Kapazität 10
}

// Konstruktor mit Parameter für die Datenbank
Bibliothek::Bibliothek(const string& dbName) : db(dbName) {
    if (!db.isConnected()) {
        throw runtime_error("Fehler: Keine Verbindung zur Datenbank.");
    }
    regale.emplace_back("Regal A", 10);  // Erstelle ein Regal mit dem Namen "Regal A" und Kapazität 10
}

// Medien aus der CSV-Datei laden (inklusive Regal)
void Bibliothek::ladeMedienAusCSV() {
    auto data = CSVHandler::readCSV(medienCSV);
    for (const auto& row : data) {
        if (row.size() < 9) continue; // Mindestens 9 Spalten erwartet

        string typ = row[0];
        string autor = row[1];
        string titel = row[2];
        string kategorie = row[4];
        string code = row[5];
        string regal = row[8];  // Regal-Spalte

        if (typ == "Buch") {
            medien.push_back(make_shared<Buch>(autor, titel, kategorie, code, regal));
        }
        else if (typ == "CD") {
            medien.push_back(make_shared<CD>(autor, titel, kategorie, code, regal));
        }
        else if (typ == "DVD") {
            medien.push_back(make_shared<DVD>(autor, titel, kategorie, code, regal));
        }
        else {
            cerr << "Unbekannter Medientyp: " << typ << endl;
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
        string plz = row[3];
        string ort = row[4];
        string email = row[5];
        string telefonnummer = row[6];
        string mitgliedsnummer = row[7];

        try {
            hausnummer = stoi(row[3]); // Versuche, die Hausnummer zu konvertieren
        }
        catch (const invalid_argument& e) {
            cerr << "Ungültige Hausnummer für Nutzer mit Mitgliedsnummer: " << mitgliedsnummer << ". Fehler: " << e.what() << endl;
            continue;
        }
        catch (const out_of_range& e) {
            cerr << "Hausnummer außerhalb des Bereichs für Nutzer mit Mitgliedsnummer: " << mitgliedsnummer << ". Fehler: " << e.what() << endl;
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
        data.push_back({ m->getTyp(), m->getAutor(), m->getTitel(), m->getKategorie(), m->getCode() });
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
            n.getVorname() + "', '" + n.getNachname() + "', '" + n.getStrasse() + "', " + to_string(n.getHausnummer()) + ", '" + n.getPLZ() + "', '" + n.getOrt() + "', '" +
            n.getEmail() + "', '" + n.getTelefonnummer() + "', '" + n.getMitgliedsnummer() + "');";
        try {
            db.executeQuery(query);
        }
        catch (const exception& e) {
            cerr << "Fehler beim Hinzufügen des Nutzers zur Datenbank: " << e.what() << endl;
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

// Methode: Medium entfernen
bool Bibliothek::entferneMedium(const string& code) {
    for (auto it = medien.begin(); it != medien.end(); ++it) {
        if ((*it)->getCode() == code) {
            medien.erase(it);

            // Entfernen aus der CSV-Datei
            speichereMedienInCSV();

            // Entfernen aus der Datenbank
            if (db.isConnected()) {
                string query = "DELETE FROM Medien WHERE Code = '" + code + "';";
                try {
                    db.executeQuery(query);
                }
                catch (const exception& e) {
                    cerr << "Fehler beim Entfernen des Mediums aus der Datenbank: " << e.what() << endl;
                }
            }

            return true;
        }
    }
    return false;
}

// Methode: Nutzer entfernen
bool Bibliothek::entferneNutzer(const string& mitgliedsnummer) {
    for (auto it = nutzer.begin(); it != nutzer.end(); ++it) {
        if (it->getMitgliedsnummer() == mitgliedsnummer) {
            nutzer.erase(it);

            // Entfernen aus der CSV-Datei
            speichereNutzerInCSV();

            // Entfernen aus der Datenbank
            if (db.isConnected()) {
                string query = "DELETE FROM Nutzer WHERE Mitgliedsnummer = '" + mitgliedsnummer + "';";
                try {
                    db.executeQuery(query);
                }
                catch (const exception& e) {
                    cerr << "Fehler beim Entfernen des Nutzers aus der Datenbank: " << e.what() << endl;
                }
            }

            return true;
        }
    }
    return false;
}

// Methode: Medium hinzufügen
void Bibliothek::fuegeMediumHinzu(const std::string& typ, const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal) {
    // Füge das Medium basierend auf dem Typ hinzu
    if (typ == "Buch") {
        medien.push_back(std::make_shared<Buch>(autor, titel, kategorie, code, regal));
    }
    else if (typ == "CD") {
        medien.push_back(std::make_shared<CD>(autor, titel, kategorie, code, regal));
    }
    else if (typ == "DVD") {
        medien.push_back(std::make_shared<DVD>(autor, titel, kategorie, code, regal));
    }
    else {
        std::cerr << "Unbekannter Medientyp: " << typ << std::endl;
    }
}



// Methode: Nutzer hinzufügen
void Bibliothek::fuegeNutzerHinzu(const string& vorname, const string& nachname, const string& strasse, int hausnummer, const string& plz, const string& ort, const string& email, const string& telefonnummer, const string& mitgliedsnummer) {
    // Nutzer zur internen Liste hinzufügen
    nutzer.emplace_back(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);

    // Nutzer zur CSV-Datei hinzufügen
    vector<vector<string>> data = {
        { vorname, nachname, strasse, to_string(hausnummer), plz, ort, email, telefonnummer, mitgliedsnummer }
    };
    CSVHandler::writeCSVAppend(nutzerCSV, data);

    // Nutzer in die Datenbank speichern, falls verbunden
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



// Neue Methode: Suche nach Medien basierend auf einem Kriterium (Autor, Titel, Kategorie)
std::vector<std::shared_ptr<Medien>> Bibliothek::sucheMedien(const std::string& suchbegriff, const std::string& kriterium) const {
    std::vector<std::shared_ptr<Medien>> ergebnisse;

    for (const auto& medium : medien) {
        if ((kriterium == "Autor" && medium->getAutor().find(suchbegriff) != std::string::npos) ||
            (kriterium == "Titel" && medium->getTitel().find(suchbegriff) != std::string::npos) ||
            (kriterium == "Kategorie" && medium->getKategorie().find(suchbegriff) != std::string::npos)) {
            ergebnisse.push_back(medium);
        }
    }
    return ergebnisse;
}

// Neue Methode: Suche nach Nutzern basierend auf einem Kriterium (Vorname oder Nachname)
std::vector<Nutzer> Bibliothek::sucheNutzer(const std::string& suchbegriff, const std::string& kriterium) const {
    std::vector<Nutzer> ergebnisse;

    for (const auto& nutzer : this->nutzer) {
        if ((kriterium == "Vorname" && nutzer.getVorname().find(suchbegriff) != std::string::npos) ||
            (kriterium == "Nachname" && nutzer.getNachname().find(suchbegriff) != std::string::npos)) {
            ergebnisse.push_back(nutzer);
        }
    }
    return ergebnisse;
}

// Methode zum Abrufen der Liste der Nutzer
std::vector<Nutzer> Bibliothek::getNutzer() const {
    return nutzer;
}

// Methode zum Abrufen der Liste der Medien
std::vector<std::shared_ptr<Medien>> Bibliothek::getMedien() const {
    return medien;
}
// Die Methode für die Anzeige von Büchern in einem bestimmten Regal (nur eine Version)
void Bibliothek::zeigeBuecherInRegal(const string& regName) const {
    cout << "Bücher im Regal '" << regName << "':" << endl;
    for (const auto& medium : medien) {
        if (medium->getRegal() == regName && medium->getTyp() == "Buch") {
            cout << "Autor: " << medium->getAutor()
                << " | Titel: " << medium->getTitel()
                << " | Kategorie: " << medium->getKategorie()
                << " | Code: " << medium->getCode() << endl;
        }
    }
}