#include "Bibliothek.hpp"
#include "Medien.hpp"
#include "Regal.hpp"
#include "Buch.hpp"
#include "CD.hpp"
#include "DVD.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>  // Für std::string::find Methode

using namespace std;

// Standardkonstruktor
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


bool Bibliothek::entferneNutzer(const std::string& mitgliedsnummer) {
    for (auto it = nutzer.begin(); it != nutzer.end(); ++it) {
        if (it->getMitgliedsnummer() == mitgliedsnummer) {
            nutzer.erase(it);
            speichereNutzerInCSV();
            speichereNutzerInDatenbank();
            return true;
        }
    }
    return false;
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

        // Füge den Nutzer hinzu
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
            << " | Code: " << m->getCode() << endl;
    }
    cout << "-----------------" << endl;
}

// Nutzer in der Konsole auflisten
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
            << " | Mitgliedsnummer: " << n.getMitgliedsnummer() << endl;
    }
    cout << "-----------------" << endl;
}

// Methode: Medium entfernen
bool Bibliothek::entferneMedium(const string& code) {
    for (auto it = medien.begin(); it != medien.end(); ++it) {
        if ((*it)->getCode() == code) {
            medien.erase(it);

            speichereMedienInCSV();
            return true;
        }
    }
    return false;
}

// Methode: Medium hinzufügen
void Bibliothek::fuegeMediumHinzu(const std::string& typ, const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal) {
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
        cerr << "Unbekannter Medientyp: " << typ << endl;
    }
}

// Methode: Nutzer hinzufügen
void Bibliothek::fuegeNutzerHinzu(const string& vorname, const string& nachname, const string& strasse, int hausnummer, const string& plz, const string& ort, const string& email, const string& telefonnummer, const string& mitgliedsnummer) {
    nutzer.emplace_back(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);
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

// Methode: Zeige Medien im Regal
void Bibliothek::zeigeMedienInRegal(const std::string& regName) const {
    for (const auto& regal : regale) {
        if (regal.getName() == regName) {
            std::cout << "Medien im Regal '" << regName << "':" << std::endl;
            regal.displayInhalte();
            return;
        }
    }
    std::cerr << "Regal '" << regName << "' nicht gefunden." << std::endl;
}

// Methode: Zeige Bücher im Regal (case-insensitive)
void Bibliothek::zeigeBuecherInRegal(const string& regName) const {
    if (regName.empty()) {
        cerr << "Ungültige Eingabe: Der Regalname darf nicht leer sein. Beispiel für eine gültige Eingabe: Regal-1." << endl;
        return;
    }

    string regNameLower = regName;
    std::transform(regNameLower.begin(), regNameLower.end(), regNameLower.begin(),
        [](unsigned char c) { return std::tolower(c); });

    bool buchGefunden = false;

    cout << "Bücher im Regal '" << regName << "':" << endl;

    for (const auto& medium : medien) {
        string mediumRegalLower = medium->getRegal();
        std::transform(mediumRegalLower.begin(), mediumRegalLower.end(), mediumRegalLower.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (mediumRegalLower == regNameLower && medium->getTyp() == "Buch") {
            cout << "Autor: " << medium->getAutor()
                << " | Titel: " << medium->getTitel()
                << " | Kategorie: " << medium->getKategorie()
                << " | Code: " << medium->getCode() << endl;
            buchGefunden = true;
        }
    }

    if (!buchGefunden) {
        cerr << "Keine Bücher im Regal '" << regName << "' gefunden. Beispiel für gültige Eingabe: Regal-1." << endl;
    }
}
