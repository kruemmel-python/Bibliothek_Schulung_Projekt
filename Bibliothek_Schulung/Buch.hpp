#ifndef BUCH_HPP
#define BUCH_HPP

#include "Medien.hpp"

class Buch : public Medien {
public:
    Buch(const std::string& autor, const std::string& titel, const std::string& kategorie, const std::string& code, const std::string& regal); // F�ge Regal hinzu

    std::string getTyp() const override;
    std::string getRegal() const; // Methode zum Abrufen des Regals

private:
    std::string regal; // F�ge das Regal als Mitgliedsvariable hinzu
};

#endif // BUCH_HPP
