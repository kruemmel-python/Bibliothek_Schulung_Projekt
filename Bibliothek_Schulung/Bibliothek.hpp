// Bibliothek.hpp

#ifndef BIBLIOTHEK_HPP
#define BIBLIOTHEK_HPP

#include <vector>
#include <memory>
#include "Medien.hpp"
#include "Nutzer.hpp"
#include "CSVHandler.hpp"
#include "Datenbankverbindung.hpp"
#include "Regal.hpp"

class Bibliothek {
public:
    Bibliothek();
    Bibliothek(const std::string& dbName);

    // Neue Methode zur Anzeige von Büchern in einem Regal
    void zeigeBuecherInRegal(const std::string& regName) const;

    // **Füge diese Zeile hinzu:**
    void zeigeMedienInRegal(const std::string& regName) const;

    std::vector<std::shared_ptr<Medien>> sucheMedien(const std::string& suchbegriff, const std::string& kriterium) const;
    std::vector<Nutzer> sucheNutzer(const std::string& suchbegriff, const std::string& kriterium) const;

    void ladeMedienAusCSV();
    void ladeNutzerAusCSV();
    void speichereMedienInCSV();
    void speichereNutzerInCSV();
    void speichereMedienInDatenbank();
    void speichereNutzerInDatenbank();
    void listeMedien() const;
    void listeNutzer() const;

    void fuegeMediumHinzu(const std::string& typ, const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal);
    // Regal hinzugefügt
    void fuegeNutzerHinzu(const std::string& vorname, const std::string& nachname, const std::string& strasse, int hausnummer, const std::string& plz, const std::string& ort, const std::string& email, const std::string& telefonnummer, const std::string& mitgliedsnummer);

    bool entferneMedium(const std::string& code);
    bool entferneNutzer(const std::string& mitgliedsnummer);

    std::vector<Nutzer> getNutzer() const;
    std::vector<std::shared_ptr<Medien>> getMedien() const;

private:
    std::vector<std::shared_ptr<Medien>> medien;
    std::vector<Nutzer> nutzer;
    std::vector<Regal> regale;

    Datenbankverbindung db;

    const std::string medienCSV = "bibliothek.csv";
    const std::string nutzerCSV = "nutzer.csv";
};

#endif // BIBLIOTHEK_HPP
