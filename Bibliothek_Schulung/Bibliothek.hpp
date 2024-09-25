#ifndef BIBLIOTHEK_HPP
#define BIBLIOTHEK_HPP

#include <vector>
#include <memory>
#include "Medien.hpp"
#include "Nutzer.hpp"
#include "CSVHandler.hpp"
#include "Datenbankverbindung.hpp"

class Bibliothek {
public:
    Bibliothek(const std::string& dbName);

    void ladeMedienAusCSV();
    void ladeNutzerAusCSV();

    void speichereMedienInCSV();
    void speichereNutzerInCSV();

    void speichereMedienInDatenbank();
    void speichereNutzerInDatenbank();

    void listeMedien() const;
    void listeNutzer() const;

    // Neue Methoden zum Hinzufügen von Medien und Nutzern
    void fuegeMediumHinzu(const std::string& typ, const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code);
    void fuegeNutzerHinzu(const std::string& vorname, const std::string& nachname, const std::string& strasse, int hausnummer, const std::string& plz, const std::string& ort, const std::string& email, const std::string& telefonnummer, const std::string& mitgliedsnummer);

private:
    std::vector<std::shared_ptr<Medien>> medien;
    std::vector<Nutzer> nutzer;
    Datenbankverbindung db;

    const std::string medienCSV = "bibliothek.csv";
    const std::string nutzerCSV = "nutzer.csv";
};

#endif // BIBLIOTHEK_HPP
