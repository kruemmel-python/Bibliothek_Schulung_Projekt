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


// Konstruktor, initialisiert die Verbindung zur Datenbank
Bibliothek::Bibliothek(const std::string& dbName) : db(dbName) {
    if (!db.isConnected()) {
        throw std::runtime_error("Fehler: Keine Verbindung zur Datenbank.");
    }
}

// Medien aus der CSV-Datei laden
void Bibliothek::ladeMedienAusCSV() {
    auto data = CSVHandler::readCSV(medienCSV);
    for (const auto& row : data) {
        if (row.size() < 7) continue; // Mindestens 7 Spalten erwartet

        std::string typ = row[0];
        std::string autor = row[1];
        std::string titel = row[2];
        std::string kategorie = row[4];
        std::string code = row[5];

        if (code.empty()) {
            std::cerr << "Fehler: Medientyp " << typ << " hat keinen Code." << std::endl;
            continue;
        }

        if (typ == "Buch") {
            medien.push_back(std::make_shared<Buch>(autor, titel, kategorie, code));
        }
        else if (typ == "CD") {
            medien.push_back(std::make_shared<CD>(autor, titel, kategorie, code));
        }
        else if (typ == "DVD") {
            medien.push_back(std::make_shared<DVD>(autor, titel, kategorie, code));
        }
    }
}

// Nutzer aus der CSV-Datei laden
void Bibliothek::ladeNutzerAusCSV() {
    auto data = CSVHandler::readCSV(nutzerCSV);

    // Überprüfe, ob die erste Zeile die Spaltenüberschriften sind und überspringe diese
    bool ersteZeileIstUeberschrift = true;  // Falls die erste Zeile Überschriften enthält
    for (const auto& row : data) {
        if (ersteZeileIstUeberschrift) {
            ersteZeileIstUeberschrift = false;
            continue;  // Überspringe die erste Zeile
        }

        if (row.size() < 9) continue; // Mindestens 9 Spalten erwartet

        std::string vorname = row[0];
        std::string nachname = row[1];
        std::string strasse = row[2];
        int hausnummer = 0;
        std::string plz = row[4];
        std::string ort = row[5];
        std::string email = row[6];
        std::string telefonnummer = row[7];
        std::string mitgliedsnummer = row[8];

        // Fehlerbehandlung für ungültige Hausnummer
        try {
            hausnummer = std::stoi(row[3]); // Versuche, die Hausnummer zu konvertieren
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ungültige Hausnummer für Nutzer mit Mitgliedsnummer: "
                << mitgliedsnummer << std::endl;
            continue;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Hausnummer außerhalb des Bereichs für Nutzer mit Mitgliedsnummer: "
                << mitgliedsnummer << std::endl;
            continue;
        }

        // Wenn alles gültig ist, füge den Nutzer hinzu
        nutzer.emplace_back(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);
    }
}

// Medien in die CSV-Datei speichern
void Bibliothek::speichereMedienInCSV() {
    std::vector<std::vector<std::string>> data;
    for (const auto& m : medien) {
        data.push_back({ m->getTyp(), m->getAutor(), m->getTitel(), "", m->getKategorie(), m->getCode(), "", "" });
    }
    CSVHandler::writeCSV(medienCSV, data);
}

// Nutzer in die CSV-Datei speichern
void Bibliothek::speichereNutzerInCSV() {
    std::vector<std::vector<std::string>> data;
    for (const auto& n : nutzer) {
        data.push_back({ n.getVorname(), n.getNachname(), n.getStrasse(), std::to_string(n.getHausnummer()),
                        n.getPLZ(), n.getOrt(), n.getEmail(), n.getTelefonnummer(), n.getMitgliedsnummer() });
    }
    CSVHandler::writeCSV(nutzerCSV, data);
}

// Medien in die Datenbank speichern
void Bibliothek::speichereMedienInDatenbank() {
    if (!db.isConnected()) {
        std::cerr << "Fehler: Keine Verbindung zur Datenbank." << std::endl;
        return;
    }
    for (const auto& m : medien) {
        std::string query = "INSERT INTO Medien (Typ, Autor, Titel, Kategorie, Code) VALUES ('" +
            m->getTyp() + "', '" + m->getAutor() + "', '" + m->getTitel() + "', '" +
            m->getKategorie() + "', '" + m->getCode() + "');";
        try {
            db.executeQuery(query);
        }
        catch (const std::exception&) {
            std::cerr << "Fehler beim Speichern des Mediums in die Datenbank." << std::endl;
        }
    }
}

// Nutzer in die Datenbank speichern
void Bibliothek::speichereNutzerInDatenbank() {
    if (!db.isConnected()) {
        std::cerr << "Fehler: Keine Verbindung zur Datenbank." << std::endl;
        return;
    }
    for (const auto& n : nutzer) {
        std::string query = "INSERT INTO Nutzer (Vorname, Nachname, Strasse, Hausnummer, PLZ, Ort, Email, Telefonnummer, Mitgliedsnummer) VALUES ('" +
            n.getVorname() + "', '" + n.getNachname() + "', '" + n.getStrasse() + "', " +
            std::to_string(n.getHausnummer()) + ", '" + n.getPLZ() + "', '" + n.getOrt() + "', '" +
            n.getEmail() + "', '" + n.getTelefonnummer() + "', '" + n.getMitgliedsnummer() + "');";
        try {
            db.executeQuery(query);
        }
        catch (const std::exception&) {
            std::cerr << "Fehler beim Speichern des Nutzers in die Datenbank." << std::endl;
        }
    }
}

// Medien in der Konsole auflisten (mit verbesserter Formatierung)
void Bibliothek::listeMedien() const {
    std::cout << "Liste der Medien:" << std::endl;
    std::cout << "-----------------" << std::endl;
    for (const auto& m : medien) {
        std::cout << "Typ: " << m->getTyp()
            << " | Autor: " << m->getAutor()
            << " | Titel: " << m->getTitel()
            << " | Kategorie: " << m->getKategorie()
            << " | Code: " << m->getCode()
            << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

// Nutzer in der Konsole auflisten (mit verbesserter Formatierung)
void Bibliothek::listeNutzer() const {
    std::cout << "Liste der Nutzer:" << std::endl;
    std::cout << "-----------------" << std::endl;
    for (const auto& n : nutzer) {
        std::cout << "Vorname: " << n.getVorname()
            << " | Nachname: " << n.getNachname()
            << " | Strasse: " << n.getStrasse()
            << " | Hausnummer: " << n.getHausnummer()
            << " | PLZ: " << n.getPLZ()
            << " | Ort: " << n.getOrt()
            << " | Email: " << n.getEmail()
            << " | Telefonnummer: " << n.getTelefonnummer()
            << " | Mitgliedsnummer: " << n.getMitgliedsnummer()
            << std::endl;
    }
    std::cout << "-----------------" << std::endl;
}

// Neue Methode: Medium hinzufügen
void Bibliothek::fuegeMediumHinzu(const std::string& typ, const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code) {
    // Medium zur internen Liste hinzufügen
    if (typ == "Buch") {
        medien.push_back(std::make_shared<Buch>(autor, titel, kategorie, code));
    }
    else if (typ == "CD") {
        medien.push_back(std::make_shared<CD>(autor, titel, kategorie, code));
    }
    else if (typ == "DVD") {
        medien.push_back(std::make_shared<DVD>(autor, titel, kategorie, code));
    }

    // Medium zur CSV-Datei hinzufügen
    std::vector<std::vector<std::string>> data = {
        { typ, autor, titel, "", kategorie, code, "", "" }
    };
    CSVHandler::writeCSVAppend(medienCSV, data);

    // Medium in die Datenbank speichern, falls vorhanden
    if (db.isConnected()) {
        std::string query = "INSERT INTO Medien (Typ, Autor, Titel, Kategorie, Code) VALUES ('" +
            typ + "', '" + autor + "', '" + titel + "', '" + kategorie + "', '" + code + "');";
        try {
            db.executeQuery(query);
        }
        catch (const std::exception& e) {
            std::cerr << "Fehler beim Hinzufügen des Mediums zur Datenbank: " << e.what() << std::endl;
        }
    }
}

// Neue Methode: Nutzer hinzufügen
void Bibliothek::fuegeNutzerHinzu(const std::string& vorname, const std::string& nachname, const std::string& strasse, int hausnummer, const std::string& plz, const std::string& ort, const std::string& email, const std::string& telefonnummer, const std::string& mitgliedsnummer) {
    // Nutzer zur internen Liste hinzufügen
    nutzer.emplace_back(vorname, nachname, strasse, hausnummer, plz, ort, email, telefonnummer, mitgliedsnummer);

    // Nutzer zur CSV-Datei hinzufügen
    std::vector<std::vector<std::string>> data = {
        { vorname, nachname, strasse, std::to_string(hausnummer), plz, ort, email, telefonnummer, mitgliedsnummer }
    };
    CSVHandler::writeCSVAppend(nutzerCSV, data);

    // Nutzer in die Datenbank speichern, falls vorhanden
    if (db.isConnected()) {
        std::string query = "INSERT INTO Nutzer (Vorname, Nachname, Strasse, Hausnummer, PLZ, Ort, Email, Telefonnummer, Mitgliedsnummer) VALUES ('" +
            vorname + "', '" + nachname + "', '" + strasse + "', " + std::to_string(hausnummer) + ", '" + plz + "', '" + ort + "', '" +
            email + "', '" + telefonnummer + "', '" + mitgliedsnummer + "');";
        try {
            db.executeQuery(query);
        }
        catch (const std::exception& e) {
            std::cerr << "Fehler beim Hinzufügen des Nutzers zur Datenbank: " << e.what() << std::endl;
        }
    }
}
